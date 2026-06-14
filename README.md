# tenvex

A header-only C++20 SIMD math library for 4D vector arithmetic.

tenvex uses **expression templates** — a C++ template metaprogramming technique that allows chained vector operations to be evaluated lazily. A compound expression such as `norm3(a + b * 2.0f) * dot3(b, c) + c * 3.0f` is evaluated, at the point of assignment, as a single sequence of SSE4.1 (x86-64) or NEON (ARM64) intrinsics without intermediate temporaries.

## License

BSD 3-Clause License. Copyright (c) 2026 Artem Zyktin. See [LICENSE.txt](LICENSE.txt).

## Status

**Implemented and tested**

- **x86-64 / SSE4.1**
- **ARM64 / NEON** (Cortex-A76 / Raspberry Pi 5, GCC and Clang)

**Planned**

- Quaternions
- Matrices

## Features

- Header-only - just include `tenvex.h`.
- Expression-template engine: nodes are lazy and evaluated on assignment.
- C++20 concepts (`expression`, `vec_expr`, `scalar_expr`) enforce type safety at compile time.
- Storage policy: small trivially-copyable nodes are stored by value, larger ones by `const&`, which also avoids dangling references to temporary sub-expressions.
- Operations: `+`, `-` (binary), `-` (unary negation), `*` (scalar), `/` (by scalar), `dot3`, `dot4`, `cross3`, `norm3`, `magnitude3`, `magnitude3_sq`, `min`, `max`, `abs`, `hadamard` (component-wise), `floor`, `ceil`, `round`, `frac` (rounding), `clamp`, `saturate`, `lerp`, `dist3`, `dist3_sq`, `reflect` (composed), `==`, `approx_eq`, and component accessors `x()`, `y()`, `z()`, `w()`.

## Requirements

- A C++20 compiler (MSVC, GCC, or Clang).
- One of: an x64 CPU with **SSE4.1**, or an **ARM64 / NEON** CPU (AArch64). The backend is selected automatically in `expressions/config.h`.
- Premake for generating the test build (binaries are bundled for Windows, Linux, and macOS; an AArch64 premake binary is included for ARM64 Linux).

## Getting Started

tenvex is header-only. Copy `src/tenvex/` into your project and include the single public header:

```cpp
#include "tenvex.h"
```

### Basic Usage

```cpp
#include "tenvex.h"

using namespace tnvx;

vec4 a = { 1.0f, 2.0f, 3.0f, 0.0f };
vec4 b = { 4.0f, 5.0f, 6.0f, 0.0f };
vec4 c = { 1.0f, 0.0f, 1.0f, 0.0f };

// Arithmetic
vec4 sum     = a + b;
vec4 diff    = a - b;
vec4 scaled  = a * 2.0f;     // vector * scalar
vec4 scaled2 = 3.0f * b;     // scalar * vector
vec4 halved  = a / 2.0f;     // vector / scalar

// Vector operations (3-component; the w / homogeneous lane is handled explicitly)
float d    = dot3(a, b);       // 3D dot product (ignores w)
float d4   = dot4(a, b);       // 4D dot product (includes w) - e.g. plane . point
vec4  cr   = cross3(a, b);     // 3D cross product, result w = 0
vec4  n    = norm3(a);         // normalize xyz, w preserved
float mag  = magnitude3(a);    // 3D length (ignores w)
float mag2 = magnitude3_sq(a); // 3D length squared, no sqrt - use for distance compares

// Component-wise min / max (all 4 lanes, including w) - e.g. growing an AABB
vec4 lo = min(a, b);           // per-lane minimum
vec4 hi = max(a, b);           // per-lane maximum
vec4 av = abs(a);              // per-lane absolute value (clears sign bit)
vec4 hp = hadamard(a, b);      // per-lane product (a.x*b.x, ...) - colors, non-uniform scale

// Rounding (SSE4.1 native, per-lane)
vec4 fl = floor(a);            // round toward -inf
vec4 cl2 = ceil(a);            // round toward +inf
vec4 rn = round(a);            // nearest, half-to-even (matches HLSL round / GLSL roundEven)
vec4 fr = frac(a);             // fractional part in [0,1); wraps negatives (texture REPEAT)

// Composed operations (free functions, eager - return concrete vec4 / float)
vec4  cl = clamp(a, lo, hi);   // per-lane clamp to [lo, hi]
vec4  sa = saturate(a);        // clamp to [0, 1]
vec4  mi = lerp(a, b, 0.5f);   // linear interpolation; t is float or scalar_expr
float di = dist3(a, b);        // 3D distance
float d2 = dist3_sq(a, b);     // 3D distance squared, no sqrt
vec4  rf = reflect(a, b);      // reflect a about (unit) normal b

// Negation (unary minus) - works on any expression node, stays lazy
vec4 neg_a   = -a;
vec4 neg_expr = -(a + b);          // Neg<Add<vec4,vec4>>  - still lazy
float neg_d  = -dot3(a, b);        // Neg<Dot3<...>>       - still scalar_expr

// Compound expression - evaluated lazily, no temporaries, fused on assignment
vec4 result = norm3(a + b * 2.0f) * dot3(b, c) + c * 3.0f;
```

`dot3` and `magnitude3` return scalar-expression nodes (`Dot3`, `Magn3`) that are implicitly convertible to `float` (the scalar is taken from lane 0), so `float d = dot3(a, b);` works, and they can also be used as operands inside a larger lazy expression.

### `vec4`

`vec4` is a 16-byte, `alignas(16)` value type. It can be default-constructed, built from components (with `w` defaulting to `0`), or constructed from any vector expression (which triggers evaluation):

```cpp
vec4 zero;                                   // default
vec4 v = { 1.0f, 2.0f, 3.0f };               // w defaults to 0
vec4 p = { 1.0f, 2.0f, 3.0f, 1.0f };         // explicit w
vec4 r = a + b * 2.0f;                        // built from an expression (evaluates here)

vf4 raw = v.eval();                           // underlying __m128
```

Individual components are read on demand from the stored register; `vec4` keeps no separate float copy:

```cpp
float cx = v.x();   // lane 0
float cy = v.y();   // lane 1
float cz = v.z();   // lane 2
float cw = v.w();   // lane 3
```

### Comparison

```cpp
vec4 a = { 1.0f, 2.0f, 3.0f, 4.0f };
vec4 b = { 1.0f, 2.0f, 3.0f, 4.0f };

bool exact   = (a == b);               // exact, all-lane equality
bool approx1 = approx_eq(a, b);        // default epsilon = 1e-6f
bool approx2 = approx_eq(a, b, 1e-3f); // custom epsilon
```

## Architecture

### Two layers

- **Eager kernel layer** (`expressions/core.h`, namespace `tnvx::detail`): `TNVX_INLINE` functions over `vf4` (`neg`, `abs`, `add`, `sub`, `mul`, `div`, `dot3`, `dot4`, `magnitude3`, `magnitude3_sq`, `norm3`, `cross3`, `min`, `max`, `scalar`, `get_lane`, `eq`, `approx_eq`). This is the only place intrinsics live, and the only place the SIMD backend is selected: `core.h` dispatches to `core_sse.h` (SSE4.1) or `core_neon.h` (NEON) per the autodetected target.
- **Expression layer** (everything else in namespace `tnvx`): lazy nodes that compose and delegate down to the kernels. This layer operates only on `vf4` and contains no intrinsics.

### Expression templates

Every operation returns a lazy node rather than evaluating immediately. Nodes inherit from `Expr<Derived>` via CRTP (which provides `self()`) and expose a `vf4 eval() const` method. Evaluation happens only when the result is assigned to a `vec4`, or - for scalar nodes - when converted to `float`.

```
vec4 result = norm3(a + b * 2.0f) * dot3(b, c) + c * 3.0f;
//            Add< Mul< Norm3< Add<vec4, Mul<vec4, Scalar>> >, Scalar >, Mul<vec4, Scalar> >
//            evaluated as one SSE4.1 sequence at assignment
```

### C++20 concepts

| Concept          | Meaning                                                                 |
| ---------------- | ----------------------------------------------------------------------- |
| `expression<T>`  | Derives from `Expr<T>` and has `eval() -> vf4` and `self() -> const T&` |
| `vec_expr<T>`    | An `expression` marked as a vector expression (`is_vec_expr<T>`)        |
| `scalar_expr<T>` | An `expression` marked as a scalar expression (`is_scalar_expr<T>`)     |

### Storage policy

Each node's operands are stored by value or by `const&` depending on size and triviality. This avoids dangling references to temporary sub-expressions:

```cpp
// trivially copyable && trivially destructible && sizeof(T) <= 16  ->  stored by value
// otherwise                                                        ->  stored as const T&
template<typename T>
using tnvx_ref_or_value_t =
    std::conditional_t<is_stored_by_value_v<T>, T, const T&>;
```

### Operation nodes

The **Intrinsics** column lists the SSE4.1 (x86-64) backend; the NEON (AArch64) backend in `core_neon.h` provides the same operations with the corresponding `v*q_f32` / `vld1q` / table-permute equivalents.

| Node          | Concept       | Intrinsics                                                  | Notes                                                                       |
| ------------- | ------------- | ----------------------------------------------------------- | --------------------------------------------------------------------------- |
| `Neg<E>`      | vec / scalar  | `_mm_xor_ps` (sign mask)                                   | Unary negation; result is `vec_expr` when E is `vec_expr`, `scalar_expr` when E is `scalar_expr`; both stay lazy |
| `Abs<E>`      | `vec_expr`    | `_mm_andnot_ps` (sign mask)                                | Component-wise absolute value; clears the sign bit of each lane (pure bit op, not arithmetic) |
| `Scalar`      | `scalar_expr` | `_mm_set_ps1`                                               | Broadcasts a `float` to all 4 lanes                                         |
| `Add<L,R>`    | `vec_expr`    | `_mm_add_ps`                                                |                                                                             |
| `Sub<L,R>`    | `vec_expr`    | `_mm_sub_ps`                                                |                                                                             |
| `Mul<L,R>`    | vec / scalar  | `_mm_mul_ps`                                                | Scalar multiply only (no component-wise `vec * vec`). Operands may be vector×scalar, scalar×vector, or scalar×scalar; a scalar operand is a `float` or a scalar expression |
| `Div<L,R>`    | `vec_expr`    | `_mm_div_ps`                                                | Vector divided by a scalar (`float`)                                        |
| `Dot3<L,R>`   | `scalar_expr` | `_mm_mul_ps` + shuffles + `_mm_add_ss`                      | 3-component dot (ignores w), broadcast to all lanes; convertible to `float` |
| `Dot4<L,R>`   | `scalar_expr` | `_mm_mul_ps` + `_mm_hadd_ps` x2                             | 4-component dot (includes w), broadcast to all lanes; convertible to `float` |
| `Cross3<L,R>` | `vec_expr`    | `_mm_shuffle_ps` + `_mm_mul_ps` + `_mm_sub_ps`              | 3-component cross product; result `w = 0`                                   |
| `Norm3<E>`    | `vec_expr`    | `dot3` + `_mm_sqrt_ps` + `_mm_div_ps` + `_mm_blend_ps`      | Normalizes xyz by the 3D magnitude; preserves w                             |
| `Magn3<E>`    | `scalar_expr` | `_mm_sqrt_ps` + `dot3(v,v)`                                  | 3-component length (ignores w), broadcast; convertible to `float`           |
| `Magn3Sq<E>`  | `scalar_expr` | `dot3(v,v)`                                                 | 3-component length squared (no `sqrt`); broadcast; convertible to `float`   |
| `Min<L,R>`    | `vec_expr`    | `_mm_min_ps`                                                | Component-wise minimum across all 4 lanes                                   |
| `Max<L,R>`    | `vec_expr`    | `_mm_max_ps`                                                | Component-wise maximum across all 4 lanes                                   |
| `Hadamard<L,R>` | `vec_expr`  | `_mm_mul_ps`                                               | Component-wise (per-lane) product; named, not `operator*`, to avoid ambiguity with dot/cross |
| `Floor<E>`    | `vec_expr`    | `_mm_floor_ps`                                             | Per-lane floor (round toward -inf)                                         |
| `Ceil<E>`     | `vec_expr`    | `_mm_ceil_ps`                                              | Per-lane ceiling (round toward +inf)                                       |
| `Round<E>`    | `vec_expr`    | `_mm_round_ps` (nearest)                                   | Per-lane round, half-to-even (matches HLSL `round` / GLSL `roundEven`)      |
| `Frac<E>`     | `vec_expr`    | `_mm_sub_ps(v, floor(v))`                                  | Per-lane fractional part in [0,1); floor-based, wraps negatives correctly   |

Comparison helpers (free functions in `tnvx`, backed by `tnvx::detail`):

| Function                     | Intrinsics                              | Notes                          |
| ---------------------------- | --------------------------------------- | ------------------------------ |
| `operator==`                 | `_mm_cmpeq_ps` + `_mm_movemask_ps`      | Exact, all-lane equality       |
| `approx_eq(a, b, eps=1e-6f)` | `_mm_andnot_ps` + `_mm_cmple_ps` + mask | Per-lane abs difference <= eps |

### Composed operations

Free functions in `tnvx` that compose the operators above. **They evaluate eagerly and return concrete types** (`vec4` / `float`), not expression nodes - returning a lazy expression that references function-local temporaries would dangle. Defined in `expressions/operations.h` (declarations) / `operations_impl.hpp` (definitions), included last in `tenvex.h`.

| Function           | Returns | Composition                | Notes                                                                     |
| ------------------ | ------- | -------------------------- | ------------------------------------------------------------------------- |
| `clamp(v, lo, hi)` | `vec4`  | `min(max(v, lo), hi)`      | Per-lane clamp                                                            |
| `saturate(v)`      | `vec4`  | `clamp(v, 0, 1)`           | Clamp to [0, 1]                                                          |
| `lerp(a, b, t)`    | `vec4`  | `a + (b - a) * t`          | Two overloads: `float t` (by value) and `scalar_expr t` (folds in lazily) |
| `dist3(l, r)`      | `float` | `magnitude3(l - r)`        | 3D distance                                                               |
| `dist3_sq(l, r)`   | `float` | `magnitude3_sq(l - r)`     | No sqrt - use for distance compares                                       |
| `reflect(v, n)`    | `vec4`  | `v - n * (dot3(v, n) * 2)` | Reflect `v` about unit normal `n`                                         |

## Building

The build uses [Premake5](https://premake.github.io/); binaries are bundled in `premake/bin/` for all platforms (including an AArch64 binary for ARM64 Linux). The workspace defines two platforms, **x64** and **ARM64**, uses C++20, with `debug` and `release` configurations and `tenvex_tests` as the start project. On GCC/Clang the `-msse4.1` flag is applied to the **x64** platform only (NEON is the baseline on AArch64 and needs no flag); projects that consume the SSE4.1 path must enable SSE4.1 in their own build.

### Windows (Visual Studio 2026)

```bat
scripts\config-vs2026.bat
```

Then open the generated solution under `build/`, pick the **x64** or **ARM64** platform, and build the `tenvex_tests` project. (An ARM64 selection produces a Windows-on-ARM build for compile-checking only; run the tests and benchmarks natively on an AArch64 Linux target.)

### Linux / macOS

```sh
# Linux (x64)
./premake/bin/linux/premake5 gmake2

# Linux (ARM64 / AArch64) - uses the bundled AArch64 premake
./scripts/config-gmake-arm64.sh

# macOS
./premake/bin/macos/premake5 gmake2

# then (the config name carries the platform suffix)
make config=release_x64      # or: release_arm64, debug_x64, debug_arm64
```

Build output is written to `bin/<system>/<arch>/<debug|release>/output/`.

## Running Tests

The test suite uses Google Test (vendored in `thirdparty/gtest/`) and currently covers 88 cases:

| Category             | Tests                                                                                                      |
| -------------------- | ---------------------------------------------------------------------------------------------------------- |
| Basic operations     | `add`, `sub`, `mult_a`, `mult_b`, `div`, `dot3`, `cross`, `norm_a`, `norm_b`, `magnitude_a`, `magnitude_b`, `magnitude3_sq_a`, `magnitude3_sq_b` |
| Compound expressions | `mixed_type_add`, `expression_a`, `expression_b`, `expression_c`, `expression_d`, `expression_from_temporaries` |
| Math properties      | `cross_anticommutative`, `dot_commutative`, `norm_magnitude`, `dot_perpendicular`, `cross_parallel`, `w_is_zero_with_nonzero_input_w`, `preserves_nontrivial_w`, `zero_vector_is_nan` |
| Type system          | `dot3_times_literal_collapses`, `magnitude3_times_literal_collapses`                                       |
| Unary negation       | `neg_basic`, `neg_zero`, `neg_double`, `neg_compound`, `neg_expression`, `neg_scalar_stays_lazy`, `neg_scalar_in_expression` |
| 4D dot product       | `dot4_basic`, `dot4_w_zero_matches_dot3`, `dot4_w_matters`, `dot4_w_only`, `dot4_perpendicular`, `dot4_commutative`, `dot4_collapses` |
| Component-wise min/max | `min_basic`, `max_basic`, `min_negatives`, `max_negatives`, `min_includes_w`, `min_idempotent`, `min_commutative` |
| Absolute value       | `abs_basic`, `abs_all_negative`, `abs_already_positive`, `abs_zero`, `abs_expression` |
| Clamp / saturate     | `clamp_basic`, `clamp_custom_range`, `clamp_within_range`, `clamp_all_below`, `clamp_all_above`, `clamp_expression`, `saturate_basic`, `saturate_within_range`, `saturate_clamps_negatives`, `saturate_clamps_above_one` |
| Interpolation        | `lerp_at_zero`, `lerp_at_one`, `lerp_half`, `lerp_expression` |
| Distance / reflect   | `dist3_basic`, `dist3_zero`, `dist3_ignores_w`, `dist3_sq_basic`, `dist3_sq_zero`, `reflect_off_horizontal`, `reflect_scaled`, `reflect_diagonal`, `reflect_expression` |
| Hadamard product     | `hadamard_basic`, `hadamard_includes_w`, `hadamard_commutative`, `hadamard_expression` |
| Rounding             | `floor_basic`, `floor_already_integer`, `ceil_basic`, `round_basic`, `round_half_to_even`, `frac_basic` |

Build and run `tenvex_tests` from the generated project or makefile.

## Benchmarks

A [Google Benchmark](https://github.com/google/benchmark) suite (vendored in `thirdparty/benchmark/`) lives in `src/benchmarks/` and is built as the `tenvex_bench` project. Build in **release** and run the resulting executable (on GCC/Clang, `-msse4.1` is applied on the x64 platform; NEON needs no flag on AArch64). A subset can be selected at runtime, e.g. `tenvex_bench --benchmark_filter=Compound`.

Cases cover both **latency** (serial dependency chains, e.g. `dot3`/`norm3`, and an AABB-box build that folds `min`/`max` into a running bound) and **throughput** (independent inputs the CPU can pipeline, e.g. isolated `dot3`/`dot4`, and single-op `min`/`max`).

A naive scalar reference implementation - `naive::vec4` in `src/naive/naive_vec4.h` - mirrors the tenvex API and semantics with plain `float` math (everything `inline`, by-value, reciprocal-multiply for division/normalization). It is benchmarked side by side (the `BM_Naive_*` cases) and has its own mirrored test suite (`src/tests/naive_tests.cpp`), so the SIMD path can be compared against a straightforward baseline.

### Is the abstraction zero-cost? (compiler x backend)

tenvex's core claim is that the lazy expression template compiles to the *same* machine code as hand-written intrinsics. To check this, the compound expression `norm3(va[i] + vb[i] * 2.0f) * dot3(vb[i], vc[i]) + vc[i] * 3.0f` is benchmarked three ways over an array: through the expression template (`BM_Compound_tenvex`), through the same `tnvx::detail` kernels written out as explicit statements (`BM_Compound_manual_kernels`), and through hand-written raw intrinsics (`BM_Compound_intrinsics`). When the abstraction is zero-cost, all three are equal.

They are equal on every target tested but one - and "zero-cost" turns out to be a property of the *(compiler x backend)* pair, not of the abstraction alone:

| Compiler  | x86-64                     | AArch64 (NEON)                    |
| --------- | -------------------------- | --------------------------------- |
| **MSVC**  | zero-cost (3.20 ~ 3.03 ns) | -                                 |
| **GCC**   | zero-cost (identical asm)  | **~36% slower** (9.09 vs 6.66 ns) |
| **Clang** | zero-cost (pending)        | zero-cost (6.56 ns, all equal)    |

*Representative numbers from the reference machines (AMD Zen 3 / MSVC; Raspberry Pi 5 Cortex-A76 / GCC and Clang). The verdict - zero-cost or not - is read from disassembly and is machine-independent.*

The single outlier is **GCC on AArch64**. Disassembly of the loop shows the kernels themselves are identical across all three variants; the difference is entirely the expression tree. GCC's AArch64 backend materializes the expression object - the by-value 16-byte `vec4` leaves plus scalar constants, about 128 bytes - onto a stack frame and emits several dead vector stores per iteration (`str` / `stp` to `[sp]`) that are never read back; the actual arithmetic runs in registers regardless. MSVC, GCC/x86-64, and Clang on both ISAs scalarize that object away completely (full SROA) and emit zero stores. It is a missed dead-store elimination in one optimizer backend, not a flaw in the storage policy - three of the four cells are perfect.

A note on method: a standalone function taking `const vec4&` arguments does **not** reproduce the overhead (its disassembly is clean). The dead stores appear only under the real loop access pattern - array-indexed leaves, with `vb[i]` and `vc[i]` used twice, captured by value. A microbenchmark has to mirror the actual access pattern or it hides the very thing being measured.

**Practical guidance.** On ARM, build tenvex with **Clang** - the abstraction is free there. Under GCC/AArch64, in a hot loop, bind a shared sub-expression to a `vec4` (or evaluate leaves to `vf4`) before reusing it; this is the same "bind to a value" rule that already pays for repeated sub-expressions, and it removes the stack frame.

### Findings

- **Zero-cost on three of four (compiler x backend) cells** - see the matrix above. The one exception (GCC/AArch64) is a backend codegen limitation, not an abstraction cost.
- Arithmetic-heavy compound expressions beat the scalar baseline; isolated `dot3` / `norm3` do not - a 3-component horizontal reduction gains little from SIMD. This holds on both SSE and NEON; NEON's native `vaddvq` reduction does not rescue it.
- Single-input element-wise ops (`abs`, `floor`, `saturate`, ...) collapse to the same time for tenvex and the scalar baseline - they are memory-bandwidth bound, so SIMD width is irrelevant.
- Compare ratios **within one compiler**: the scalar baseline itself shifts between compilers (e.g. the naive compound differs by roughly 20% between GCC and Clang on the same CPU), so "Nx vs naive" is only meaningful when both sides use the same toolchain.
- These are per-vec4 figures. Bulk / SoA throughput is a separate track.