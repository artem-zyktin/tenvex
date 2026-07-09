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
