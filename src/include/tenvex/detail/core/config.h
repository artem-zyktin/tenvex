#pragma once

#if !defined(TNVX_SSE41) && !defined(TNVX_NEON)

// x86 SSE4.1
#if defined(__SSE4_1__)
#define TNVX_SSE41 1
#elif defined(_MSC_VER) && defined(_M_X64)
#define TNVX_SSE41 1
#endif

// arm neon
#if defined(__ARM_NEON) || defined(__ARM_NEON__)
#define TNVX_NEON 1
#elif defined(_MSC_VER) && defined(_M_ARM64)
#define TNVX_NEON 1
#endif

#endif

#if !defined(TNVX_SSE41) && !defined(TNVX_NEON)
#error "tenvex: no SIMD backend detected. tenvex requires SSE4.1 (x86-64) or NEON (AArch64). \
On x64 with GCC/Clang enable SSE4.1 in the consuming target (-msse4.1, or a wider -march=...); \
MSVC x64 and AArch64 need no flags. To override detection, define TNVX_SSE41=1 or TNVX_NEON=1 manually."
#endif
