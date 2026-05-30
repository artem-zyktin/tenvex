#pragma once

#include "config.h"
#include "defines.h"

#if defined(HAS_SSE42)
#include <smmintrin.h>
using vf4 = __m128;
#else
#endif

namespace tnvx::detail
{

[[nodiscard]] TNVX_INLINE
bool eq(vf4 a, vf4 b)
{
	return _mm_movemask_ps(_mm_cmpeq_ps(a, b)) == 0b1111;
}

[[nodiscard]] TNVX_INLINE
bool approx_eq(vf4 a, vf4 b, float eps) noexcept
{
	vf4 abs_diff = _mm_andnot_ps(_mm_set1_ps(-0.0f), _mm_sub_ps(a, b));
	return _mm_movemask_ps(_mm_cmple_ps(abs_diff, _mm_set1_ps(eps))) == 0b1111;
}

[[nodiscard]] TNVX_INLINE
vf4 scalar(float value) noexcept
{
	return _mm_set_ps1(value);
}

[[nodiscard]] TNVX_INLINE
vf4 add(vf4 l, vf4 r) noexcept
{
	return _mm_add_ps(l, r);
}

[[nodiscard]] TNVX_INLINE
vf4 sub(vf4 l, vf4 r) noexcept
{
	return _mm_sub_ps(l, r);
}

[[nodiscard]] TNVX_INLINE
vf4 mul(vf4 l, vf4 r) noexcept
{
	return _mm_mul_ps(l, r);
}

[[nodiscard]] TNVX_INLINE
vf4 div(vf4 l, vf4 r) noexcept
{
	return _mm_div_ps(l, r);
}

[[nodiscard]] TNVX_INLINE
vf4 dot3(vf4 l, vf4 r) noexcept
{
	return _mm_dp_ps(l, r, 0b01111111);
}

[[nodiscard]] TNVX_INLINE
vf4 magnitude3(vf4 v) noexcept
{
	return _mm_sqrt_ps(_mm_dp_ps(v, v, 0b01111111));
}

[[nodiscard]] TNVX_INLINE
vf4 norm3(vf4 v) noexcept
{
	return _mm_blend_ps(_mm_div_ps(v, magnitude3(v)), v, 0b1000);
}

[[nodiscard]] TNVX_INLINE
vf4 cross3(vf4 l, vf4 r) noexcept
{
	vf4 a_yzx = _mm_shuffle_ps(l, l, _MM_SHUFFLE(3, 0, 2, 1));
	vf4 b_yzx = _mm_shuffle_ps(r, r, _MM_SHUFFLE(3, 0, 2, 1));

	vf4 t = _mm_sub_ps(_mm_mul_ps(l, b_yzx),
					   _mm_mul_ps(a_yzx, r));

	return _mm_shuffle_ps(t, t, _MM_SHUFFLE(3, 0, 2, 1));
}

}
