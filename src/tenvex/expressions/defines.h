#pragma once

#if defined(_MSC_VER)
#define TNVX_INLINE __forceinline
#define TNVX_RESTRICT __restrict
#elif defined(__GNUC__) || defined(__clang__)
#define TNVX_INLINE __attribute__((always_inline)) inline
#define TNVX_RESTRICT __restrict__
#else
#define TNVX_INLINE inline
#define TNVX_RESTRICT
#endif
