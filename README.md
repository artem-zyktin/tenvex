# tenvex

A header-only C++20 SIMD math library for 4D vector and quaternion arithmetic.

tenvex uses **expression templates** — a C++ template metaprogramming technique that allows chained vector operations to be evaluated lazily. A compound expression such as `norm3(a + b * 2.0f) * dot3(b, c) + c * 3.0f` is evaluated, at the point of assignment, as a single sequence of SSE4.1 (x86-64) or NEON (ARM64) intrinsics without intermediate temporaries.

## License

BSD 3-Clause License. Copyright (c) 2026 Artem Zyktin. See [LICENSE.txt](LICENSE.txt).

## Status

**Implemented and tested**

- **x86-64 / SSE4.1**
- **ARM64 / NEON** (Cortex-A76 / Raspberry Pi 5, GCC and Clang)

Both backends cover the full API.

**Planned**

- Matrices

## Features

- Header-only - just include `tenvex.h`.
- Expression-template engine: nodes are lazy and evaluated on assignment.
- C++20 concepts (`expression`, `vec_expr`, `scalar_expr`, `quat_expr`, `packed_expr`) enforce type safety at compile time.
- Storage policy: leaves (trivially-copyable, 16 bytes or less) are stored by value; larger composite nodes by `const&`. Because that reference can outlive a temporary sub-expression, assign compound expressions to a `vec4` / `float` rather than `auto` (see [Performance and best practices](#performance-and-best-practices)).
- Operations: `+`, `-` (binary), `-` (unary negation), `*` (scalar), `/` (by scalar), `dot3`, `dot4`, `cross3`, `norm3`, `norm3_fast` (approximate, see below), `magnitude3`, `magnitude3_sq`, `magnitude4`, `magnitude4_sq`, `min`, `max`, `abs`, `hadamard` (component-wise), `floor`, `ceil`, `round`, `frac` (rounding), `clamp`, `saturate`, `lerp`, `dist3`, `dist3_sq`, `reflect` (composed), `==`, `approx_eq`, ordered magnitude comparisons (`<`, `<=`, `>`, `>=` on `magnitude3`, see [Comparison](#comparison)), and component accessors `x()`, `y()`, `z()`, `w()`. The 4-lane reductions `dot4`, `magnitude4`, and `magnitude4_sq` accept a `quat` as well as a `vec4`.
- A `quat` type with Hamilton product (`*`), `conj`, `normalize`, `inverse`, `rotate`, `slerp`, `nlerp`, and the usual `+`, `-`, scalar `*`, `==`, `approx_eq` (see [Quaternions](#quaternions)).

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
float mag4 = magnitude4(a);    // 4D length (includes w)
float m4sq = magnitude4_sq(a); // 4D length squared, no sqrt

// Component-wise min / max (all 4 lanes, including w) - e.g. growing an AABB
vec4 lo = min(a, b);           // per-lane minimum
vec4 hi = max(a, b);           // per-lane maximum
vec4 av = abs(a);              // per-lane absolute value (clears sign bit)
vec4 hp = hadamard(a, b);      // per-lane product (a.x*b.x, ...) - colors, non-uniform scale
vec4 pw = with_w(a + b, a);    // xyz from a+b, keep a's w (tag / radius / material id)

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

// Quaternions (w is the scalar / real part; there is no identity() - use { 0, 0, 0, 1 })
quat q  = { 0.0f, 0.0f, 0.70710678f, 0.70710678f }; // 90 deg about +Z
quat qc = conj(q);        // conjugate: negate xyz, keep w (inverse of a unit quaternion)
quat qh = q * q;          // Hamilton product - composes rotations (non-commutative)
vec4 vr = rotate(a, q);   // rotate a vec4 by a unit quaternion
```

`dot3` and `magnitude3` return scalar-expression nodes (`Dot3`, `Magn3`) that are implicitly convertible to `float` (the scalar is taken from lane 0), so `float d = dot3(a, b);` works, and they can also be used as operands inside a larger lazy expression.

`with_w(value, w_source)` writes xyz from `value` and the w lane from `w_source` in a single blend - the library keeps the choice of *which* w survives at the call site instead of baking it into per-op `add3` / `mul3` variants.

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

**Ordered magnitude comparisons.** The relational operators `<`, `<=`, `>`, `>=` on `magnitude3` compare lengths *without computing either square root*. Because length is non-negative, ordering by length and ordering by squared length agree, so the comparison is rewritten to run on `magnitude3_sq` (a `dot3`, no `sqrt`):

```cpp
vec4 a = { ... }, b = { ... };

bool closer = magnitude3(a) < magnitude3(b);   // no sqrt on either side
bool inside = magnitude3(a) < radius;          // one sqrt removed; precondition: radius >= 0
bool outside = 8.0f < magnitude3(a);           // scalar on either side
```

This is the only place in the library where the result is **not** bit-identical to the naive `length(a) < length(b)`: the squared form is in fact *more* discriminating near rounding collisions, and on the comparison path the abstraction is faster than the naive baseline (the compiler cannot prove the `sqrt` away on its own). Notes:

- **Precondition for the scalar form:** the threshold must be non-negative (`magnitude3(a) < c` assumes `c >= 0`). A negative threshold is a caller error and is not checked.
- **`==` / `!=` are deliberately *not* de-`sqrt`'d** — they fall back to the exact `float` length (two real `sqrt`s), since equality of lengths is exactly where rounding collisions bite hardest.
- **NaN:** if any input is NaN the magnitude is NaN and all four relations read `false`, matching the IEEE behaviour of the exact path.
- **Dynamic range caveat:** squaring doubles the exponent range, so the de-`sqrt` form can overflow on planetary/astronomical coordinates (and underflow on tiny vectors) where the exact `sqrt` form would not. For graphics-scale data this never triggers.

## Quaternions

`quat` is a 16-byte, `alignas(16)` value type laid out as `(x, y, z, w)` with **`w` the scalar (real) part** and `xyz` the vector part. Like `vec4`, it can be default-constructed, built from four components, or constructed from any quaternion expression (which triggers evaluation). There is deliberately no `identity()` helper - the identity is the literal `{ 0, 0, 0, 1 }`.

```cpp
quat id = { 0.0f, 0.0f, 0.0f, 1.0f };               // identity
quat q  = { 0.0f, 0.0f, 0.70710678f, 0.70710678f }; // 90 deg about +Z
quat r  = q * q;                                     // built from an expression (evaluates here)

float qw = q.w();                                    // lane 3 = scalar part
vf4  raw = q.eval();                                 // underlying __m128
```

Operations (all lazy nodes, evaluated on assignment, same as vectors):

```cpp
quat c = conj(q);          // Conj      - negate xyz, keep w; for a unit quaternion this is its inverse
quat n = normalize(q);     // Normalize - scale to unit length (q / magnitude4(q)); stays a quat node
quat iv = inverse(q);      // Inverse   - conj(q) / magnitude4_sq(q); equals conj for a unit quaternion
quat h = q1 * q2;          // QuatMul   - Hamilton product; non-commutative; composes rotations
quat a = q1 + q2;          // Add / Sub - component-wise, stay quaternion-typed
quat s = q * 2.0f;         // scalar *  - scales all four lanes (float or scalar_expr)

vec4 vr = rotate(v, q);    // Rotate    - rotate vec4 v by unit quaternion q; result is a vec4

// Interpolation (composed convenience - eager, return a concrete quat, assume unit inputs)
quat sl = slerp(q1, q2, 0.5f); // spherical linear interp; shortest arc; constant angular velocity
quat nl = nlerp(q1, q2, 0.5f); // normalized lerp; cheaper (no acos/sin), approximate for large arcs

bool same = (q1 == q2);        // exact, all-lane equality
bool near = approx_eq(q1, q2); // default epsilon = 1e-6f
```

`rotate(v, q)` returns the rotated **vector** (a `vec_expr`, so it stays lazy and can feed a larger expression); the `w` lane of `v` is carried through unchanged. It uses the cross-product form `v + 2w(n x v) + 2(n x (n x v))` (with `n = q.xyz`, `w = q.w`), which is the sandwich `q * v * conj(q)` for a **unit** `q` - the unit precondition is assumed, not checked. `conj`, `normalize`, `inverse`, `*`, `+`, `-`, and `rotate` are lazy nodes: the same "assign to a concrete type, don't hold a compound expression in `auto`" rule from [Performance and best practices](#performance-and-best-practices) applies to quaternion expressions too. `slerp` and `nlerp` are composed convenience functions - like `lerp` / `reflect` on vectors they evaluate eagerly and return a concrete `quat`. Both assume unit-length inputs, take the shortest arc (via the sign of `dot4`), and fall back to a normalized lerp when the inputs are nearly parallel; `nlerp` skips the `acos` / `sin` entirely, trading constant angular velocity for speed.

## Performance and best practices

tenvex is zero-overhead when used the way the optimizer expects. A few rules keep the generated code tight and steer around the one real footgun.

**Assign expressions to `vec4` / `float`; don't keep them in `auto`.** Operators and operations (`+`, `*`, `norm3`, `dot3`, ...) return *lazy nodes*, not values. A node stores operands of 16 bytes or less by value, but larger composite operands by `const&` (see [Storage policy](#storage-policy)). Those references point at sub-expression *temporaries* that die at the end of the full statement, so holding a compound expression in `auto` and using it afterwards dangles:

```cpp
auto e   = norm3(a + b * 2.0f);  // BAD: the inner Add<...> temporary is already dead here
vec4 bad = e * dot3(b, c);       //      e.eval() reads a dangling reference -> garbage / inf / crash

vec4 t    = norm3(a + b * 2.0f); // GOOD: assigning to vec4 evaluates immediately
vec4 good = t * dot3(b, c);
```

Assigning to a `vec4` (or converting a scalar node to `float`) forces evaluation, which is what you want at the point of use anyway. `auto` is only safe when every operand outlives the expression - rarely worth the reasoning; just assign.

**Bind a reused sub-expression to a value.** Nodes are pure - they carry no cache - so a sub-expression that appears twice in one statement is computed twice. If you reuse a term, evaluate it once into a `vec4`:

```cpp
vec4 r1 = norm3(a + b * 2.0f) * dot3(a + b * 2.0f, c); // 'a + b * 2.0f' built twice -> work done twice

vec4 t  = a + b * 2.0f;                                // shared term computed once
vec4 r2 = norm3(t) * dot3(t, c);
```

This is the right "cache". A mutable caching node would defeat the compiler's common-subexpression elimination and is a pessimization for small SIMD expressions; an explicit `vec4` binding has zero overhead and lets the compiler fuse freely.

**Prefer the squared forms for comparisons.** `magnitude3_sq` and `dist3_sq` skip the `sqrt`. Use them whenever you only compare or threshold a distance (`dist3_sq(a, b) < r * r`) rather than needing the metric value. The ordered `magnitude3` comparisons (`magnitude3(a) < magnitude3(b)`, `magnitude3(a) < r`) apply the same trick automatically — see [Comparison](#comparison).

**`norm3_fast` is not universally faster — measure before reaching for it.** `norm3_fast` replaces the exact `sqrt` + `div` of `norm3` with a hardware reciprocal-sqrt estimate refined by one Newton-Raphson step. Its result is approximate (near full `float` precision after the Newton step) and its speed is *backend- and mode-dependent*:

| | throughput | latency (dependent chain) |
| ---------------- | ---------- | ------------------------- |
| x86-64 / SSE4.1  | ~1.1x faster | ~1.1x faster |
| ARM64 / NEON     | ~1.1x faster | **~1.0x — slightly slower** |

On Cortex-A76 the Newton-Raphson refinement is a 5-link dependency chain versus the 2 links of `fsqrt` + `fdiv`, so on the critical path `norm3_fast` *loses* to exact `norm3`. Use it only where normalization is throughput-bound, or x86-only, and never assume the folklore "rsqrt is faster" without checking your target. `norm3` remains the correct default; `norm3_fast` is an opt-in for callers who have measured a win.

**Know where SIMD actually helps.** Reach for tenvex on *fused, arithmetic-heavy per-vector expressions* - that is where the lazy template earns its keep. It helps less, or not at all, in two cases worth knowing up front:

| Pattern                                                       | Expectation                                                          |
| ------------------------------------------------------------- | ------------------------------------------------------------------- |
| Fused compound (`norm3(a + b*2) * dot3(b,c) + c*3`)           | Clear win over the scalar baseline                                  |
| Isolated horizontal reduction (`dot3`, `norm3` on their own)  | Little gain - the cross-lane sum dominates, on SSE and NEON alike   |
| Single-input element-wise pass over an array (`abs`, `floor`, `saturate`) | Memory-bandwidth bound - same time as scalar; SIMD width is irrelevant |

**In a GCC/AArch64 hot loop, bind leaves to a value (or build that unit with Clang).** This is the one *(compiler x backend)* pair with an abstraction cost (see [Is the abstraction zero-cost?](#is-the-abstraction-zero-cost-compiler-x-backend)). Binding the leaf vectors to `vec4` / `vf4` before building the expression removes the dead stack frame GCC/AArch64 would otherwise materialize; compiling that translation unit with Clang avoids it entirely.

## Architecture

### Two layers

- **Eager kernel layer** (`expressions/core.h`, namespace `tnvx::detail`): `TNVX_INLINE` functions over `vf4` (`neg`, `abs`, `add`, `sub`, `mul`, `div`, `dot3`, `dot4`, `magnitude3`, `magnitude3_sq`, `magnitude4`, `magnitude4_sq`, `norm3`, `cross3`, `min`, `max`, `scalar`, `get_lane`, `eq`, `approx_eq`, and the quaternion kernels `conjugate`, `quat_mul`, `rotate`, `normalize`, `inverse`). This is the only place intrinsics live, and the only place the SIMD backend is selected: `core.h` dispatches to `core_sse.h` (SSE4.1) or `core_neon.h` (NEON) per the autodetected target.
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
| `quat_expr<T>`   | An `expression` marked as a quaternion expression (`is_quat_expr<T>`)   |
| `packed_expr<T>` | A `vec_expr` or `quat_expr` — a 4-lane packed value, as opposed to a collapsed scalar |
| `same_packed_category<L,R>` | Two `packed_expr` of the same category (both vectors or both quaternions); the operand rule for `dot4` |

### Storage policy

Each node's operands are stored by value or by `const&` depending on size and triviality. Leaves are small and stored by value; only larger composite nodes are held by `const&`. That reference can point at a temporary sub-expression, so a compound expression must not be kept in `auto` past its statement (see [Performance and best practices](#performance-and-best-practices)):

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
| `Dot4<L,R>`   | `scalar_expr` | `_mm_mul_ps` + `_mm_hadd_ps` x2                             | 4-component dot (includes w), broadcast to all lanes; convertible to `float`; operands are two vectors or two quaternions (`same_packed_category`) |
| `Cross3<L,R>` | `vec_expr`    | `_mm_shuffle_ps` + `_mm_mul_ps` + `_mm_sub_ps`              | 3-component cross product; result `w = 0`                                   |
| `Norm3<E>`    | `vec_expr`    | `dot3` + `_mm_sqrt_ps` + `_mm_div_ps` + `_mm_blend_ps`      | Normalizes xyz by the 3D magnitude; preserves w                             |
| `Norm3Fast<E>` | `vec_expr`   | `dot3` + `_mm_rsqrt_ps` + Newton step + `_mm_mul_ps`        | Approximate normalize via reciprocal-sqrt estimate; preserves w; backend-dependent speed (see [Performance](#performance-and-best-practices)) |
| `Magn3<E>`    | `scalar_expr` | `_mm_sqrt_ps` + `dot3(v,v)`                                  | 3-component length (ignores w), broadcast; convertible to `float`           |
| `Magn3Sq<E>`  | `scalar_expr` | `dot3(v,v)`                                                 | 3-component length squared (no `sqrt`); broadcast; convertible to `float`   |
| `Magn4<E>`    | `scalar_expr` | `_mm_sqrt_ps` + `dot4(v,v)`                                 | 4-component length (includes w), for a vector or quaternion (`packed_expr`); broadcast; convertible to `float` |
| `Magn4Sq<E>`  | `scalar_expr` | `dot4(v,v)`                                                 | 4-component length squared (no `sqrt`), for a vector or quaternion (`packed_expr`); broadcast; convertible to `float` |
| `Min<L,R>`    | `vec_expr`    | `_mm_min_ps`                                                | Component-wise minimum across all 4 lanes                                   |
| `Max<L,R>`    | `vec_expr`    | `_mm_max_ps`                                                | Component-wise maximum across all 4 lanes                                   |
| `Hadamard<L,R>` | `vec_expr`  | `_mm_mul_ps`                                               | Component-wise (per-lane) product; named, not `operator*`, to avoid ambiguity with dot/cross |
| `WithW<L,R>`  | `vec_expr`    | `_mm_blend_ps` (lane 3)                                     | xyz from the first operand, w from the second - a single blend, no arithmetic. The w-source is chosen explicitly at the call site (rather than a fixed `add3` / `mul3` convention); stays lazy |
| `Floor<E>`    | `vec_expr`    | `_mm_floor_ps`                                             | Per-lane floor (round toward -inf)                                         |
| `Ceil<E>`     | `vec_expr`    | `_mm_ceil_ps`                                              | Per-lane ceiling (round toward +inf)                                       |
| `Round<E>`    | `vec_expr`    | `_mm_round_ps` (nearest)                                   | Per-lane round, half-to-even (matches HLSL `round` / GLSL `roundEven`)      |
| `Frac<E>`     | `vec_expr`    | `_mm_sub_ps(v, floor(v))`                                  | Per-lane fractional part in [0,1); floor-based, wraps negatives correctly   |
| `Conj<E>`     | `quat_expr`   | `_mm_xor_ps` (sign mask on xyz)                            | Quaternion conjugate: negates xyz, keeps w; involutive; inverse of a unit quaternion |
| `Normalize<E>` | `quat_expr`  | `dot4(q,q)` + `_mm_sqrt_ps` + `_mm_div_ps`                | Scales a quaternion to unit length (`q / magnitude4(q)`); stays a `quat_expr` (vectors use `norm3`) |
| `Inverse<E>`  | `quat_expr`   | `conjugate` + `dot4(q,q)` + `_mm_div_ps`                   | Quaternion inverse `conj(q) / magnitude4_sq(q)`; equals `conj` for a unit quaternion |
| `QuatMul<L,R>` | `quat_expr`  | shuffles + `_mm_mul_ps` + `_mm_xor_ps` + `_mm_add_ps`      | Hamilton product (`operator*` on two `quat_expr`); non-commutative; composes rotations |
| `Rotate<V,Q>` | `vec_expr`    | `cross3` x2 + `_mm_mul_ps` + `_mm_add_ps`                  | Rotates vector V by unit quaternion Q via `v + 2w(n x v) + 2(n x (n x v))`; result is a `vec_expr`, w carried from V |

Comparison helpers (free functions in `tnvx`, backed by `tnvx::detail`):

| Function                     | Intrinsics                              | Notes                          |
| ---------------------------- | --------------------------------------- | ------------------------------ |
| `operator==`                 | `_mm_cmpeq_ps` + `_mm_movemask_ps`      | Exact, all-lane equality       |
| `approx_eq(a, b, eps=1e-6f)` | `_mm_andnot_ps` + `_mm_cmple_ps` + mask | Per-lane abs difference <= eps |

### Composed operations

Free functions in `tnvx` that compose the operators above. **They evaluate eagerly and return concrete types** (`vec4` / `float`), not expression nodes - returning a lazy expression that references function-local temporaries would dangle. Defined in `expressions/operations.h` (declarations) / `operations_impl.hpp` (definitions), included last in `tenvex.h`; the quaternion convenience functions `slerp` / `nlerp` live alongside in `expressions/quat_operations.h`.

| Function           | Returns | Composition                | Notes                                                                     |
| ------------------ | ------- | -------------------------- | ------------------------------------------------------------------------- |
| `clamp(v, lo, hi)` | `vec4`  | `min(max(v, lo), hi)`      | Per-lane clamp                                                            |
| `saturate(v)`      | `vec4`  | `clamp(v, 0, 1)`           | Clamp to [0, 1]                                                          |
| `lerp(a, b, t)`    | `vec4`  | `a + (b - a) * t`          | Two overloads: `float t` (by value) and `scalar_expr t` (folds in lazily) |
| `dist3(l, r)`      | `float` | `magnitude3(l - r)`        | 3D distance                                                               |
| `dist3_sq(l, r)`   | `float` | `magnitude3_sq(l - r)`     | No sqrt - use for distance compares                                       |
| `reflect(v, n)`    | `vec4`  | `v - n * (dot3(v, n) * 2)` | Reflect `v` about unit normal `n`                                         |
| `slerp(a, b, t)`   | `quat`  | shortest-path + `acos` / `sin` arc | Spherical linear interpolation of unit quaternions; constant angular velocity; falls back to `nlerp` when near-parallel. In `quat_operations.h` |
| `nlerp(a, b, t)`   | `quat`  | shortest-path + `normalize(lerp)` | Normalized lerp; cheaper than `slerp` (no `acos` / `sin`), approximate for large arcs. In `quat_operations.h` |

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

### Compiler choice and optimization

tenvex only collapses to tight code with optimization on. Build the consuming target in **release** (`-O3` on GCC/Clang, `/O2` on MSVC); a debug build leaves the expression nodes as real calls and will be slow - that is expected, not a regression.

**Compiler per platform.** On **x86-64**, GCC, Clang, and MSVC are all zero-cost - use whichever you already have. On **AArch64**, prefer **Clang**: it is zero-cost, whereas GCC's AArch64 backend adds roughly a third to compound expressions (a missed dead-store elimination, detailed under [Is the abstraction zero-cost?](#is-the-abstraction-zero-cost-compiler-x-backend)). If you must use GCC on AArch64, bind reused leaves to a `vec4` in hot loops.

**SSE4.1 is an x64-only flag.** tenvex does not force `-msse4.1` onto consumers. On x64 with GCC/Clang you must enable it yourself (`-msse4.1`, or a wider arch such as `-march=native`); on AArch64, NEON is the baseline and needs no flag. The backend is then selected automatically in `expressions/config.h` from `__SSE4_1__` / `__ARM_NEON` (and `_M_X64` / `_M_ARM64` on MSVC) - there is no manual switch.

**LTO and mixing compilers.** The bundled `release` configuration enables link-time optimization, and LTO bytecode is tied to the exact compiler and version that produced it - a build tree must not mix them. When you switch compiler or version, clean first:

```sh
make clean config=release_arm64
make config=release_arm64 CC=clang CXX=clang++
```

A stale object from another toolchain surfaces at link time as `bytecode stream ... generated with LTO version X instead of the expected Y`; the fix is always a clean rebuild with one consistent compiler (or a separate build directory per toolchain).

## Running Tests

The test suite uses Google Test (vendored in `thirdparty/gtest/`) and covers 321 cases - 227 vector / expression and 94 quaternion. The table below groups the suite by area (representative names):

| Category             | Tests                                                                                                      |
| -------------------- | ---------------------------------------------------------------------------------------------------------- |
| Basic operations     | `add`, `sub`, `mult_a`, `mult_b`, `div`, `dot3`, `cross`, `norm_a`, `norm_b`, `magnitude_a`, `magnitude_b`, `magnitude3_sq_a`, `magnitude3_sq_b` |
| Compound expressions | `mixed_type_add`, `expression_a`, `expression_b`, `expression_c`, `expression_d`, `expression_from_temporaries` |
| Math properties      | `cross_anticommutative`, `dot_commutative`, `norm_magnitude`, `dot_perpendicular`, `cross_parallel`, `w_is_zero_with_nonzero_input_w`, `preserves_nontrivial_w`, `zero_vector_is_nan` |
| Type system          | `dot3_times_literal_collapses`, `magnitude3_times_literal_collapses`                                       |
| Unary negation       | `neg_basic`, `neg_zero`, `neg_double`, `neg_compound`, `neg_expression`, `neg_scalar_stays_lazy`, `neg_scalar_in_expression` |
| 4D dot product       | `dot4_basic`, `dot4_w_zero_matches_dot3`, `dot4_w_matters`, `dot4_w_only`, `dot4_perpendicular`, `dot4_commutative`, `dot4_collapses` |
| 4D length            | `magnitude4_basic`, `magnitude4_counts_w`, `magnitude4_is_scalar_expr`, `magnitude4_accepts_packed_rejects_scalar`, `magnitude4_sq_basic`, `magnitude4_sq_counts_w` |
| Component-wise min/max | `min_basic`, `max_basic`, `min_negatives`, `max_negatives`, `min_includes_w`, `min_idempotent`, `min_commutative` |
| Absolute value       | `abs_basic`, `abs_all_negative`, `abs_already_positive`, `abs_zero`, `abs_expression` |
| Clamp / saturate     | `clamp_basic`, `clamp_custom_range`, `clamp_within_range`, `clamp_all_below`, `clamp_all_above`, `clamp_expression`, `saturate_basic`, `saturate_within_range`, `saturate_clamps_negatives`, `saturate_clamps_above_one` |
| Interpolation        | `lerp_at_zero`, `lerp_at_one`, `lerp_half`, `lerp_expression` |
| Distance / reflect   | `dist3_basic`, `dist3_zero`, `dist3_ignores_w`, `dist3_sq_basic`, `dist3_sq_zero`, `reflect_off_horizontal`, `reflect_scaled`, `reflect_diagonal`, `reflect_expression` |
| Hadamard product     | `hadamard_basic`, `hadamard_includes_w`, `hadamard_commutative`, `hadamard_expression` |
| w-lane blend         | `with_w_basic`, `with_w_takes_w_from_source_not_value`, `with_w_source_xyz_does_not_leak`, `with_w_negative_w`, `with_w_forces_zero_w`, `with_w_value_expression`, `with_w_source_expression`, `with_w_shared_operand`, `with_w_is_vec_expr`, `with_w_composes_in_expression` |
| Rounding             | `floor_basic`, `floor_already_integer`, `floor_expression`, `ceil_basic`, `ceil_already_integer`, `ceil_expression`, `round_basic`, `round_half_to_even`, `round_expression`, `frac_basic`, `frac_expression` |
| Cross product        | `cross`, `cross_anticommutative`, `cross_parallel`, `cross_expression` |
| Quaternion type      | `construct_and_accessors`, `equality_equal`, `equality_differs`, `approx_eq_respects_epsilon`, `converting_ctor_from_expression` |
| Quaternion conjugate | `conjugate_flips_xyz_keeps_w`, `conjugate_is_quat_expr`, `conjugate_involutive` |
| Quaternion add / mul | `add_quat_quat`, `sub_quat_quat`, `add_composes_with_conjugate`, `mul_quat_float_scales_all_lanes`, `mul_float_quat`, `mul_quat_scalar_expr`, `mul_quat_scalar_disjoint_category` |
| Hamilton product     | `hamilton_product`, `hamilton_non_commutative`, `hamilton_basis_units`, `hamilton_identity`, `hamilton_associative`, `hamilton_distributes_over_add`, `hamilton_times_conjugate_is_pure_real`, `hamilton_category`, `hamilton_composes_and_scales` |
| Quaternion rotate    | `rotate_z90_axes`, `rotate_identity_is_noop`, `rotate_perpendicular_equals_cross3`, `rotate_leaves_axis_fixed`, `rotate_preserves_length`, `rotate_preserves_dot`, `rotate_composition_matches_hamilton`, `rotate_is_vec_expr` |
| Quaternion reductions | `dot4_basic`, `dot4_uses_all_four_lanes`, `dot4_commutative`, `dot4_is_scalar_expr`, `dot4_rejects_mixed_category`, `magnitude4_basic`, `magnitude4_of_unit_is_one`, `magnitude4_sq_basic` (the shared `dot4` / `magnitude4` nodes on a `quat`) |
| Quaternion normalize / inverse | `normalize_scalar_quat`, `normalize_uniform`, `normalize_yields_unit_length`, `normalize_is_quat_expr`, `inverse_scalar_quat`, `inverse_of_unit_equals_conj`, `inverse_times_self_is_identity`, `inverse_is_quat_expr` |
| Quaternion interpolation | `slerp_endpoint_start`, `slerp_endpoint_end`, `slerp_midpoint_is_halfway_arc`, `slerp_takes_shortest_path`, `slerp_preserves_unit_length`, `nlerp_midpoint_is_renormalized_chord`, `nlerp_takes_shortest_path`, `nlerp_preserves_unit_length` |

Build and run `tenvex_tests` from the generated project or makefile.

## Benchmarks

A [Google Benchmark](https://github.com/google/benchmark) suite (vendored in `thirdparty/benchmark/`) lives in `src/benchmarks/` and is built as the `tenvex_bench` project. Build in **release** and run the resulting executable (on GCC/Clang, `-msse4.1` is applied on the x64 platform; NEON needs no flag on AArch64). A subset can be selected at runtime, e.g. `tenvex_bench --benchmark_filter=Compound`.

Cases cover both **latency** (serial dependency chains, e.g. `dot3`/`norm3`, and an AABB-box build that folds `min`/`max` into a running bound) and **throughput** (independent inputs the CPU can pipeline, e.g. isolated `dot3`/`dot4`, and single-op `min`/`max`).

A naive scalar reference implementation - `naive::vec4` in `src/naive/naive_vec4.h` (and `naive::quat` in `src/naive/naive_quat.h`) - mirrors the tenvex API and semantics with plain `float` math (everything `inline`, by-value, reciprocal-multiply for division/normalization). It is benchmarked side by side (the `BM_Naive_*` cases) and has its own mirrored test suites (`src/tests/naive_tests_vec4.cpp`, `src/tests/naive_tests_quat.cpp`), so the SIMD path can be compared against a straightforward baseline. Quaternion operations are covered by `src/benchmarks/bench_quat.cpp` (`BM_Quat{Add,Sub,Mul,Hamilton,Conj,Rotate}_Throughput`; latency and throughput for the shared 4-lane reductions `BM_Quat{Dot4,Magnitude4,Magnitude4Sq}`, the unit-quaternion ops `BM_Quat{Normalize,Inverse}`, and the interpolators `BM_Quat{Slerp,Nlerp}`) against the matching `BM_Naive_Quat*` baselines. `slerp` is transcendental-bound (`acos` + `sin` dominate, so the SIMD and scalar paths run neck and neck), whereas `nlerp` shows the usual split - a small throughput win for the packed path, a latency loss to its two serial horizontal reductions. The same reductions on `vec4` are `BM_{Dot4,Magnitude4,Magnitude4Sq}` in `bench_vec4.cpp`.

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