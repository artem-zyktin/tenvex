# tenvex

A header-only C++20 SIMD math library for high-performance 4D vector arithmetic.

tenvex uses **expression templates** — a C++ template metaprogramming technique that enables lazy, zero-overhead evaluation of chained vector operations. Complex expressions like `norm(a + b * 2.0f) * dot(b, c) + c * 3.0f` compile down to a single fused sequence of SSE/AVX intrinsics with no intermediate temporaries.

## Features

- Header-only — just include `tenvex.h`
- Expression template engine with zero-cost abstractions
- All arithmetic backed by SSE/AVX intrinsics (`__m128`)
- C++20 concepts enforce type safety at compile time
- Smart storage policy: small trivial types stored by value, others by `const&`
- Supported operations: `+`, `-`, `*` (scalar), `dot`, `cross`, `norm`, `magnitude`

## Requirements

- C++20 compiler (MSVC, GCC, Clang)
- x64 CPU with SSE2 support
- [Premake5](https://premake.github.io/) (binaries included for Windows, Linux, macOS)

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

// Basic arithmetic
vec4 sum       = a + b;
vec4 diff      = a - b;
vec4 scaled    = a * 2.0f;
vec4 scaled2   = 3.0f * b;

// Vector operations
float d        = dot(a, b);
vec4  cr       = cross(a, b);
vec4  n        = norm(a);
float mag      = magnitude(a);

// Compound expressions — evaluated lazily, no temporaries
vec4 result    = norm(a + b * 2.0f) * dot(b, c) + c * 3.0f;
```

### `vec4` Member Functions

```cpp
vec4 v = { 1.0f, 2.0f, 3.0f, 4.0f };

float x   = v.x();           // component accessors
float y   = v.y();
float z   = v.z();
float w   = v.w();

auto arr  = v.data();        // std::array<float, 4>
float mag = v.magnitude();   // vector length
vec4  n   = v.norm();        // unit vector
```

### Comparison

```cpp
vec4 a = { 1.0f, 2.0f, 3.0f, 4.0f };
vec4 b = { 1.0f, 2.0f, 3.0f, 4.0f };

bool exact  = (a == b);                  // exact equality
bool approx = approx_eq(a, b);           // epsilon = 1e-3 (default)
bool approx = approx_eq(a, b, 1e-6f);   // custom epsilon
```

## Architecture

### Expression Templates

Every operation returns a lazy expression node rather than evaluating immediately. Nodes inherit from `Expr<Derived>` via CRTP and expose a single `__m128 eval() const` method. Evaluation only happens when the result is assigned to a `vec4`.

```
vec4 result = norm(a + b * 2.0f) * dot(b, c) + c * 3.0f;
//           └─ Mul<Norm<Add<vec4, Mul<vec4, Scalar>>>, Mul<Dot<vec4,vec4>, Mul<Scalar,...>>>
//              ↑ entire tree collapsed to ~5 SSE instructions at assignment
```

### C++20 Concepts

| Concept              | Meaning                                      |
|----------------------|----------------------------------------------|
| `expression<T>`      | Any `Expr<T>` subtype with `__m128 eval()`   |
| `vector_expression<T>` | An `expression` that is not a `Scalar`     |

### Storage Policy

To avoid dangling references to temporary expression nodes, storage is chosen automatically:

```cpp
// trivially copyable & destructible & sizeof <= 16  →  stored by value
// otherwise                                          →  stored as const T&
template<typename T>
using tnvx_type_storage = std::conditional_t<tnvx_store_by_value<T>, T, const T&>;
```

### Operation Nodes

| Node            | Intrinsic(s)                        | Notes                              |
|-----------------|-------------------------------------|------------------------------------|
| `Add<L,R>`      | `_mm_add_ps`                        |                                    |
| `Sub<L,R>`      | `_mm_sub_ps`                        |                                    |
| `Mul<E,Scalar>` | `_mm_mul_ps`                        | Scalar multiplication only         |
| `Dot<L,R>`      | `_mm_mul_ps` + horizontal shuffle   | Result broadcast to all 4 lanes    |
| `Cross<L,R>`    | `_mm_mul_ps` + `_mm_sub_ps` + shuffles | 3-component; w = 0              |
| `Norm<E>`       | `_mm_div_ps` + `_mm_sqrt_ps`        | Divide by magnitude                |
| `Magnitude<E>`  | `_mm_sqrt_ss`                       | Scalar result                      |
| `Scalar`        | `_mm_set1_ps`                       | Broadcasts float to all 4 lanes    |

## Building

The build system uses [Premake5](https://premake.github.io/). Premake5 binaries are included in `premake/bin/` for all platforms.

### Windows (Visual Studio 2022)

```bat
scripts\config-vs2022.bat
```

Then open the generated solution in `build/` and build the `tenvex_tests` project.

### Other Platforms

Run the appropriate Premake5 binary manually:

```sh
# Linux
./premake/bin/linux/premake5 gmake2

# macOS
./premake/bin/macos/premake5 gmake2
```

Then:

```sh
make config=debug
```

Build output is written to `bin/<system>/x64/<debug|release>/output/`.

## Running Tests

The test suite uses Google Test (vendored in `thirdparty/gtest/`) and covers 18 cases:

| Category           | Tests                                                                 |
|--------------------|-----------------------------------------------------------------------|
| Basic operations   | `add`, `sub`, `mult_a`, `mult_b`, `dot`, `cross`, `norm_a/b`, `magnitude_a/b` |
| Compound expressions | `expression_a`, `expression_b`, `expression_c`                      |
| Math properties    | `cross_anticommutative`, `dot_commutative`, `norm_magnitude`, `dot_perpendicular`, `cross_parallel` |

Build and run `tenvex_tests` from the generated project or makefile.

## Project Structure

```
tenvex/
├── src/
│   ├── tenvex/             # Library headers (header-only)
│   │   ├── tenvex.h        # Single public include
│   │   ├── vec4.h / vec4_impl.hpp
│   │   └── internal/       # Expression nodes and infrastructure
│   └── tests/
│       └── vec4_tests.cpp  # Google Test suite
├── thirdparty/
│   └── gtest/              # Vendored Google Test
├── premake/
│   └── bin/                # Premake5 binaries (Windows, Linux, macOS)
├── scripts/
│   └── config-vs2022.bat   # VS2022 project generation
└── premake5.lua            # Build configuration
```

## License

BSD 3-Clause License. Copyright (c) 2026 Artem Zyktin. See [LICENSE.txt](LICENSE.txt).
