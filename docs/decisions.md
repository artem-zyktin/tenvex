# Design decisions

Short records of decisions with non-obvious trade-offs: the problem (with
rejected alternatives), the decision, the price. Newest first. A reversal is
a new entry, not an edit.

## 2026-07 — Committed codegen listings as reviewed baseline

The zero-cost claim is verified by reading disassembly; for the article this
was manual. An automated analyzer (parse listings, count spills/frame size)
was rejected: it compresses the listing into a fixed metric set and
forecloses questions not thought of yet, and adds a Python dependency.

Decision: `src/codegen/` holds compile-only probe TUs — `extern "C"` +
`noinline`, prefix `cg_`, loop-shaped over arrays (the GCC/AArch64 dead-store
defect only reproduces under the real access pattern). Where zero-cost is
claimed, probes come in triples `_et` / `_manual` / `_intrin` with the
invariant in a header comment: loop bodies match up to register allocation.
`scripts/disasm.sh|.bat` write raw `-S` / `/FA` output per pinned toolchain
cell into `asm/`, first line records compiler version and command. `asm/` is
committed; the baseline is the last *reviewed* snapshot, not ideal code —
known defects are captured as-is. Rule: regenerate on any library change, the
diff is empty or explained; toolchain bumps are separate commits. A
`cg_clean` / `cg_spilled` pair against an opaque kernel stays as a worked
example of a spill.

Price: no automated red flag (a human reads the diff; a detector can be
layered on later), label-numbering noise in diffs, listings comparable only
within one pinned compiler version.

## 2026-07 — Header layout: category folders and group headers

`expressions/` held ~45 flat headers; `tenvex.h` was a 35-line include list
with fragile implicit ordering, about to grow by half with matrices.

Decision: split by layer and category — `core/` (intrinsics, backend
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

## 2026-07 — Remove the CRTP expression base class

`Expr<Derived>`'s only member `self()` was called nowhere except by the
concept that required it — the base existed to satisfy a check that existed
to verify the base. Its two historical purposes are obsolete: pre-C++20
operator constraining is replaced by concepts, and opt-in marking is already
provided by the category traits (default `false`, explicit specialization).

Decision: delete the base, `self()`, and the `is_base_of` requirement. A node
is any type satisfying the `expression` concept that opts into a category via
trait specialization.

Price: "this is a node" is visible only in the trait specializations, not in
the declaration line; no place for shared base members remains (deliberate —
see the `result_t` entry).

## 2026-07 — Per-node `result_t` instead of a global `vf4` in the concept

The `expression` concept required `eval() -> vf4`; matrix nodes (and later
SoA batches) evaluate to multi-register types and cannot satisfy it.
Rejected: a parallel `mat_expr` protocol — duplicates every category-generic
node and infects future utilities with `expression<T> || mat_expr<T>`
disjunctions; dropping the return-type check — admits `void` / `float` /
`const vf4&`, moves errors deep into kernel instantiation, and turns the
declared type into an unverified comment; a defaulted `result_t = vf4` in a
base class — hides the declaration behind an indirection.

Decision: every node declares `using result_t = ...;`, the concept checks
`eval()` against the node's own declaration, category concepts pin
`result_t` to `vf4`. No default anywhere: a missing declaration is a hard
error at the first constraint check.

Price: one line per node; category-generic nodes return `result_t` instead
of a literal `vf4` — one extra indirection level in template errors.
