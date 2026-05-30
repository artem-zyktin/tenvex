# tenvex

A header-only C++20 SIMD math library for high-performance 4D vector arithmetic.

tenvex uses **expression templates** - a C++ template metaprogramming technique that enables lazy, zero-overhead evaluation of chained vector operations. A compound expression such as `norm3(a + b * 2.0f) * dot3(b, c) + c * 3.0f` collapses, at the point of assignment, into a single fused sequence of SSE4.1 intrinsics with no intermediate temporaries.

## License

BSD 3-Clause License. Copyright (c) 2026 Artem Zyktin. See [LICENSE.txt](https://claude.ai/chat/LICENSE.txt).

## Status

- **x86-64 / SSE4.1** - implemented and tested.
- **ARM64 / NEON** - planned, not yet implemented.

## Features

- Header-only - just include `tenvex.h`.
- Expression-template engine with zero-cost abstractions: nodes are lazy and fuse on assignment.
- C++20 concepts (`expression`, `vec_expr`, `scalar_expr`) enforce type safety at compile time.
- Storage policy: small trivially-copyable nodes are stored by value, larger ones by `const&`, which also avoids dangling references to temporary sub-expressions.
- Operations: `+`, `-`, `*` (scalar), `/` (by scalar), `dot3`, `cross3`, `norm3`, `magnitude3`, plus `==` and `approx_eq`.

## Requirements

- A C++20 compiler (MSVC, GCC, or Clang).
- An x64 CPU with **SSE4.1** support
- Premake for generating the test build (binaries are bundled for Windows, Linux, and macOS).

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
float d   = dot3(a, b);      // 3D dot product (ignores w)
vec4  cr  = cross3(a, b);    // 3D cross product, result w = 0
vec4  n   = norm3(a);        // normalize xyz, w preserved
float mag = magnitude3(a);   // 3D length (ignores w)

// Compound expression - evaluated lazily, no temporaries, fused on assignment
vec4 result = norm3(a + b * 2.0f) * dot3(b, c) + c * 3.0f;
```

`dot3` and `magnitude3` return scalar-expression nodes (`Dot3`, `Magn3`) that are implicitly convertible to `float` (the scalar is extracted from lane 0), so both `float d = dot3(a, b);` and using them inside a larger expression work.

### `vec4`

`vec4` is a 16-byte, `alignas(16)` value type. It can be default-constructed, built from components (with `w` defaulting to `0`), or constructed from any vector expression (which triggers evaluation):

```cpp
vec4 zero;                                   // default
vec4 v = { 1.0f, 2.0f, 3.0f };               // w defaults to 0
vec4 p = { 1.0f, 2.0f, 3.0f, 1.0f };         // explicit w
vec4 r = a + b * 2.0f;                        // built from an expression (evaluates here)

vf4 raw = v.eval();                           // underlying __m128
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

- **Eager kernel layer** (`expressions/core.h`, namespace `tnvx::detail`): plain `TNVX_INLINE` functions over `vf4` (`add`, `sub`, `mul`, `div`, `dot3`, `magnitude3`, `norm3`, `cross3`, `scalar`, `eq`, `approx_eq`). This is the only place intrinsics live, and the only place the SIMD backend is selected.
- **Expression layer** (everything else in namespace `tnvx`): lazy nodes that compose and delegate down to the kernels. This layer is architecture-neutral - it only ever sees `vf4`.

### Expression templates

Every operation returns a lazy node rather than evaluating immediately. Nodes inherit from `Expr<Derived>` via CRTP (which provides `self()`) and expose a `vf4 eval() const` method. Evaluation happens only when the result is assigned to a `vec4`, or - for scalar nodes - when converted to `float`.

```
vec4 result = norm3(a + b * 2.0f) * dot3(b, c) + c * 3.0f;
//            Add< Mul< Norm3< Add<vec4, Mul<vec4, Scalar>> >, Scalar >, Mul<vec4, Scalar> >
//            ^ the whole tree collapses to a short fused SSE4.1 sequence at assignment
```

### C++20 concepts

| Concept          | Meaning                                                                 |
| ---------------- | ----------------------------------------------------------------------- |
| `expression<T>`  | Derives from `Expr<T>` and has `eval() -> vf4` and `self() -> const T&` |
| `vec_expr<T>`    | An `expression` marked as a vector expression (`is_vec_expr<T>`)        |
| `scalar_expr<T>` | An `expression` marked as a scalar expression (`is_scalar_expr<T>`)     |

### Storage policy

To keep small nodes register-friendly and to avoid dangling references to temporary sub-expressions, each node's operands are stored by value or by `const&` automatically:

```cpp
// trivially copyable && trivially destructible && sizeof(T) <= 16  ->  stored by value
// otherwise                                                        ->  stored as const T&
template<typename T>
using tnvx_ref_or_value_t =
    std::conditional_t<is_stored_by_value_v<T>, T, const T&>;
```

### Operation nodes

| Node          | Concept       | Intrinsics                                                  | Notes                                                                       |
| ------------- | ------------- | ----------------------------------------------------------- | --------------------------------------------------------------------------- |
| `Scalar`      | `scalar_expr` | `_mm_set_ps1`                                               | Broadcasts a `float` to all 4 lanes                                         |
| `Add<L,R>`    | `vec_expr`    | `_mm_add_ps`                                                |                                                                             |
| `Sub<L,R>`    | `vec_expr`    | `_mm_sub_ps`                                                |                                                                             |
| `Mul<L,R>`    | vec / scalar  | `_mm_mul_ps`                                                | Scalar multiply: `vec * float`, `float * vec`, `scalar * scalar`            |
| `Div<L,R>`    | `vec_expr`    | `_mm_div_ps`                                                | Vector divided by a scalar (`float`)                                        |
| `Dot3<L,R>`   | `scalar_expr` | `_mm_dp_ps` (mask `0x7F`)                                   | 3-component dot (ignores w), broadcast to all lanes; convertible to `float` |
| `Cross3<L,R>` | `vec_expr`    | `_mm_shuffle_ps` + `_mm_mul_ps` + `_mm_sub_ps`              | 3-component cross product; result `w = 0`                                   |
| `Norm3<E>`    | `vec_expr`    | `_mm_dp_ps` + `_mm_sqrt_ps` + `_mm_div_ps` + `_mm_blend_ps` | Normalizes xyz by the 3D magnitude; preserves w                             |
| `Magn3<E>`    | `scalar_expr` | `_mm_sqrt_ps(_mm_dp_ps(..., 0x7F))`                         | 3-component length (ignores w), broadcast; convertible to `float`           |

Comparison helpers (free functions in `tnvx`, backed by `tnvx::detail`):

| Function                     | Intrinsics                              | Notes                          |
| ---------------------------- | --------------------------------------- | ------------------------------ |
| `operator==`                 | `_mm_cmpeq_ps` + `_mm_movemask_ps`      | Exact, all-lane equality       |
| `approx_eq(a, b, eps=1e-6f)` | `_mm_andnot_ps` + `_mm_cmple_ps` + mask | Per-lane abs difference <= eps |

## Building

The build uses [Premake5](https://premake.github.io/); binaries are bundled in `premake/bin/` for all platforms. The workspace is x64-only and uses C++20, with `debug` and `release` configurations and `tenvex_tests` as the start project.

### Windows (Visual Studio 2022)

```bat
scripts\config-vs2022.bat
```

Then open the generated solution under `build/` and build the `tenvex_tests` project.

### Linux / macOS

```sh
# Linux
./premake/bin/linux/premake5 gmake2

# macOS
./premake/bin/macos/premake5 gmake2

# then
make config=debug      # or: make config=release
```

Build output is written to `bin/<system>/x64/<debug|release>/output/`.

## Running Tests

The test suite uses Google Test (vendored in `thirdparty/gtest/`) and currently covers 19 cases:

| Category             | Tests                                                                                                      |
| -------------------- | ---------------------------------------------------------------------------------------------------------- |
| Basic operations     | `add`, `sub`, `mult_a`, `mult_b`, `div`, `dot3`, `cross`, `norm_a`, `norm_b`, `magnitude_a`, `magnitude_b` |
| Compound expressions | `expression_a`, `expression_b`, `expression_c`                                                             |
| Math properties      | `cross_anticommutative`, `dot_commutative`, `norm_magnitude`, `dot_perpendicular`, `cross_parallel`        |

Build and run `tenvex_tests` from the generated project or makefile.
