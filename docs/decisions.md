# Design decisions

Short records of decisions with non-obvious trade-offs: the problem (with
rejected alternatives), the decision, the price. Newest first. A reversal is
a new entry, not an edit.

## 2026-10 - Matrices: right-handed view, clip depth [0, 1]

`look_at` / `perspective` / `orthographic` need two conventions the layout
entry below does not imply: handedness, and the clip-space depth range. They
were deliberately left out until the pair was decided. Rejected: depth
[-1, 1], the OpenGL and GLM default - it is one `glClipControl` call away on
GL and wrong on every other current API; rejected left-handed - it would
split from the same library set the `M * v` decision followed.

Decision: right-handed (the camera looks down its own -z), clip depth in
[0, 1]. The criteria are the ones already recorded for the layout: seamless
GPU upload first - Vulkan, D3D, Metal and WebGPU all want [0, 1], and GL
reaches it - then migration experience, where right-handed matches GLM,
Eigen, GLSL and Blender. `near_z` / `far_z` are positive distances in front
of the camera and `fov_y` is the full vertical angle; the names also avoid
the `near` / `far` macros the Windows SDK still defines.

Price: a caller on a [-1, 1] pipeline adjusts the range itself. The pair is
fixed rather than selectable, so a second convention means new named
constructors, not a flag - which is the point: a silent flag is how a
depth-range bug ships.

## 2026-10 - `mat_determinant` / `mat_inverse` by cofactor decomposition

A 4x4 inverse has three standard shapes. Rejected: Gauss-Jordan elimination
- pivot selection is data-dependent branching, which defeats a branch-free
SIMD kernel and makes timing input-dependent; rejected blockwise (2x2 Schur)
inversion - fewer operations, but it needs an invertible leading block, so it
is wrong for matrices this library must handle (a 90-degree rotation about x
has a singular upper-left block).

Decision: both kernels use one decomposition over the xyz parts `a,b,c,d` of
the four columns and the `w` lanes `x,y,z,w` that form row 3: `s = a x b`,
`t = c x d`, `u = a*y - b*x`, `v = c*w - d*z`, then `det = s.v + t.u`, and
the adjugate rows from four more cross products. It is branch-free, shares
its first half with the determinant, reuses `cross3` / `dot3` / `with_w`
unchanged, and is identical in both backends except `mat_transpose` and
`mat_transform`. Row 3 of the inverse falls out of the `w` lanes through
`with_w`, so the rows are assembled and transposed once at the end. A
singular matrix divides by zero and yields `inf` / `nan` lanes, matching
`normalize3` of a zero vector - not checked.

Price: the grouping is not the textbook expansion, so it is not obvious by
inspection. The naive mirror therefore keeps the textbook cofactor form
(unrolled, sharing the six 2x2 minors of each row pair) as an independent
check rather than a transcription - the two agree to 2e-4 relative over
random matrices, which is the real verification of this kernel.

## 2026-10 - Matrix nodes: `MatMul`, `Transform`, and the shared nodes' `result_t`

Three naming collisions and one promise came due when the nodes landed.
`Inverse` and `Mul` already belong to the quaternion and scalar cases, and
`Add` / `Sub` / `Neg` / `Mul` still declared `result_t = vf4`, so they could
not carry a matrix at all. Rejected: a parallel `mat_add` / `mat_sub` node
set - it duplicates four templates and the storage policy for no new
behaviour; rejected renaming the quaternion `Inverse` - a public node name
churned for a newcomer's benefit.

Decision: the matrix-only nodes are `MatMul` (the product), `Transform`
(`M * v`), `Transpose`, `Determinant` and `MatInverse`; the free functions
stay unprefixed and overloaded, so `inverse(m)` and `inverse(q)` read the
same at the call site. The shared nodes now take `result_t` from their
operands (`typename L::result_t`; for `Mul`, the non-scalar operand decides),
which is the generalization the `result_t` entry promised, and
`same_category` gained the matrix case. `Div` is deliberately left 4-lane:
scaling by a reciprocal is the same instruction and a matrix `/` would only
widen the operand matrix. The kernel layer mirrors the split - the four
element-wise kernels are overloads on `mf4` because the shared nodes
dispatch by type, while the matrix-only kernels are `mat_`-prefixed like
`mat_from_quat`.

Price: two spellings for one operation at the node level (`Inverse` vs
`MatInverse`), which the tables have to explain; `result_t` is one more
indirection in template diagnostics, as that entry already predicted.

## 2026-10 - mat4 storage: the default formula, confirmed by listing

The storage-policy entry below left the `mat4` value/ref choice to be
measured when matrices landed. No measurement was needed to pick it: 64
bytes is over the 16-byte threshold, so the existing formula already holds
leaves by `const&` with no specialization of `is_stored_by_value_v` at all.
What the listings had to confirm is that the choice costs nothing - a node
carrying an 8-byte pointer must still be scalarized away.

Decision: no per-type override for `mat4`. On the msvc1951-windows-x64 cell,
`cg_mat_transform_value` is four broadcasts, four multiplies and three adds
with no stack traffic, and - with the compiler held fixed - all seven
pre-existing probe listings are instruction-identical before and after the
`result_t` generalization (`cg_composed` only reorders two COMDAT sections).

Price: a `mat4` leaf carries the same aliasing risk as any other
by-`const&` operand, mitigated by `TNVX_RESTRICT`. `asm/` is not regenerated
in the same change: the installed compiler build differs from the one that
produced the committed cell, and a toolchain bump is a commit of its own, so
`cg_mat.asm` lags the probe set by one refresh.

## 2026-07 - `mf4` defined in each backend header; no shared types layer

NEON have no built-in 512-bit type, so matrix kernels need a named multi-register aggregate (`mf4`, four `vf4` columns) - a C array cannot be returned from `eval()`. The aggregate is backend-agnostic today, which suggested a shared home. Rejected: a `core/types.h` layer between the backend type headers and the kernels - the kernels then see `mf4` only via include order in `core.h`, recreating the implicit-ordering fragility the header-layout split removed; fixing that properly (an `arch.h` type-selection header, per-backend `types.h` / `vec.h` / `mat.h` category files) is a three-header include graph for a one-line struct.

Decision: `struct mf4 { vf4 cols[4]; };` is written directly in `core_sse.h` and `core_neon.h`, immediately after the `vf4` alias. The duplication is two frozen lines. If the type ever becomes backend-dependent, the two definitions are already the natural edit points. When a backend monolith grows painful, matrix kernels split into a private tail header included at the end of that backend file only - never from `core.h` - preserving self-sufficiency.

Price: a type defined twice; a future genuinely-shared aggregate re-opens this question (the category-folder design above is the known escape hatch).

## 2026-07 - Matrices: column-major layout, column vectors, M * v

Two coupled choices - register layout of `mf4` (rows vs columns) and the
multiplication convention (`M * v` vs `v * M`). The fast SIMD kernel is the
linear-combination form (the vector broadcasts combine the matrix
registers: 4 splats + 4 fma, no shuffles of the matrix, no horizontal
reductions; on NEON the broadcast folds into `fmla` by lane). That form
requires the pair to be consistent: column-major layout pairs with `M * v`,
row-major with `v * M`; a mismatched pair forces per-lane `dot4` reductions
or an on-the-fly transpose.

Decision criteria, in order: seamless GPU upload, then migration
experience. All current shading-language defaults are column-major
(GLSL/std140, SPIR-V, MSL, WGSL, HLSL cbuffer packing), so column-major
layout uploads as a plain memcpy on every API. The dominant user-facing
convention in the libraries tenvex would replace is `M * v` (GLM, Eigen,
Unity, GLSL source), and it is the consistent partner of column-major.

Decision: `mf4` holds four column registers; column vectors; `M * v`;
composition `T * R * S` (applied right to left). Named functions keep their
verb(object, argument) order - `rotate(v, q)` reads "rotate the vector by
the quaternion" and is unrelated to the operator convention (GLM does the
same).

Price: migrants from DirectXMath/Unreal must mirror their multiplication
order (`world * view * proj` -> `proj * view * world`); to be called out
prominently in the README matrix section.

## 2026-07 - Storage policy and matrices: no global threshold raise; per-type override only

Raising the 16-byte by-value threshold for mat4 (64 B) was considered and
rejected: the threshold also governs composite nodes, so raising it re-runs a
measured failure - all-by-value storage makes every node copy its subtree,
the expression object bloats, and GCC/AArch64 overhead grew from +39% to
+147-170% in the earlier experiment. Composite nodes stay by-`const&`
structurally; this is not a tunable.

Decision: the sanctioned per-type knob is explicit specialization of
`is_stored_by_value_v<T>` (already a variable template in
`protocol/traits.h`) - for concrete leaf value types (vec4, quat, mat4)
only, never for nodes. For mat4 the prior is by-`const&` (an 8-byte pointer
in the node versus a 64-byte copy; the risk is aliasing, mitigated by
`TNVX_RESTRICT`); the final value/ref choice is made per compiler x backend
cell by running both variants through the codegen probes (`src/codegen/`,
`asm/` listings) when matrices land, and recorded here.

Price: the storage decision for new leaf types is manual and
measurement-driven rather than automatic; the formula in `traits.h` is a
default, not the whole truth.

## 2026-07 - Committed codegen listings as reviewed baseline

The zero-cost claim is verified by reading disassembly; for the article this
was manual. An automated analyzer (parse listings, count spills/frame size)
was rejected: it compresses the listing into a fixed metric set and
forecloses questions not thought of yet, and adds a Python dependency.

Decision: `src/codegen/` holds compile-only probe TUs - `extern "C"` +
`noinline`, prefix `cg_`, loop-shaped over arrays (the GCC/AArch64 dead-store
defect only reproduces under the real access pattern). Where zero-cost is
claimed, probes come in triples `_et` / `_manual` / `_intrin` with the
invariant in a header comment: loop bodies match up to register allocation.
`scripts/disasm.sh|.bat` write raw `-S` / `/FA` output per pinned toolchain
cell into `asm/`, first line records compiler version and command. `asm/` is
committed; the baseline is the last *reviewed* snapshot, not ideal code -
known defects are captured as-is. Rule: regenerate on any library change, the
diff is empty or explained; toolchain bumps are separate commits. A
`cg_clean` / `cg_spilled` pair against an opaque kernel stays as a worked
example of a spill.

Price: no automated red flag (a human reads the diff; a detector can be
layered on later), label-numbering noise in diffs, listings comparable only
within one pinned compiler version.

## 2026-07 - Header layout: category folders and group headers

`expressions/` held ~45 flat headers; `tenvex.h` was a 35-line include list
with fragile implicit ordering, about to grow by half with matrices.

Decision: split by layer and category - `core/` (intrinsics, backend
selection), `protocol/` (traits, concepts), `common/` (category-generic
nodes and packed reductions), `vec/`, `quat/`. Each category gets a group
header (`common.h`, `vec.h`, `quat.h`) that fixes its include order once;
`tenvex.h` is three includes. Cross-folder includes are root-relative,
forward slashes only (backslashes break GCC/Clang on POSIX). Shared nodes go
to `common/` so one group never pulls another; placement follows
functionality, not result type (`rotate` lives in `quat/`). New categories
slot in as `mat.h` + `mat/`, `batch.h` + `batch/`.

Price: group-header names shadow type-header names across directories
(`expressions/quat.h` vs `expressions/quat/quat.h`); paths disambiguate.

## 2026-07 - Remove the CRTP expression base class

`Expr<Derived>`'s only member `self()` was called nowhere except by the
concept that required it - the base existed to satisfy a check that existed
to verify the base. Its two historical purposes are obsolete: pre-C++20
operator constraining is replaced by concepts, and opt-in marking is already
provided by the category traits (default `false`, explicit specialization).

Decision: delete the base, `self()`, and the `is_base_of` requirement. A node
is any type satisfying the `expression` concept that opts into a category via
trait specialization.

Price: "this is a node" is visible only in the trait specializations, not in
the declaration line; no place for shared base members remains (deliberate -
see the `result_t` entry).

## 2026-07 - Per-node `result_t` instead of a global `vf4` in the concept

The `expression` concept required `eval() -> vf4`; matrix nodes (and later
SoA batches) evaluate to multi-register types and cannot satisfy it.
Rejected: a parallel `mat_expr` protocol - duplicates every category-generic
node and infects future utilities with `expression<T> || mat_expr<T>`
disjunctions; dropping the return-type check - admits `void` / `float` /
`const vf4&`, moves errors deep into kernel instantiation, and turns the
declared type into an unverified comment; a defaulted `result_t = vf4` in a
base class - hides the declaration behind an indirection.

Decision: every node declares `using result_t = ...;`, the concept checks
`eval()` against the node's own declaration, category concepts pin
`result_t` to `vf4`. No default anywhere: a missing declaration is a hard
error at the first constraint check.

Price: one line per node; category-generic nodes return `result_t` instead
of a literal `vf4` - one extra indirection level in template errors.
