#pragma once

#include "config.h"
#include "defines.h"

#if defined(HAS_SSE41)
	#include <smmintrin.h>
	using vf4 = __m128;
#else
	#error "tenvex requires an SSE4.1 backend (define HAS_SSE41 and build with -msse4.1 on GCC/Clang)"
#endif

namespace tnvx::detail
{

[[nodscard]] TNVX_INLINE
vf4 abs(vf4 v)
{
	return _mm_andnot_ps(_mm_set1_ps(-0.0f), v);
}

[[nodiscard]] TNVX_INLINE
float to_float(vf4 v)
{
	return _mm_cvtss_f32(v);
}

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

template<int lane>
[[nodiscard]] TNVX_INLINE
float get_lane(vf4 v) noexcept
{
	return _mm_cvtss_f32(_mm_shuffle_ps(v, v, _MM_SHUFFLE(0, 0, 0, lane)));
}

[[nodiscard]] TNVX_INLINE
vf4 neg(vf4 v) noexcept
{
	return _mm_xor_ps(v, _mm_set1_ps(-0.0f));
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
	//return _mm_dp_ps(l, r, 0b01111111);
	vf4 t   = _mm_mul_ps(l, r);
	vf4 ty  = _mm_shuffle_ps(t, t, _MM_SHUFFLE(1, 1, 1, 1));
	vf4 xy  = _mm_add_ss(t, ty);
	vf4 tz  = _mm_movehl_ps(t, t);
	vf4 xyz = _mm_add_ss(xy, tz);
	return    _mm_shuffle_ps(xyz, xyz, _MM_SHUFFLE(0, 0, 0, 0));
}

[[nodiscard]] TNVX_INLINE
vf4 dot4(vf4 l, vf4 r) noexcept
{
	vf4 t = _mm_mul_ps(l, r);
	vf4 h = _mm_hadd_ps(t, t);
	return  _mm_hadd_ps(h, h);
}

[[nodiscard]] TNVX_INLINE
vf4 magnitude3(vf4 v) noexcept
{
	return _mm_sqrt_ps(dot3(v, v));
}

[[nodiscard]] TNVX_INLINE
vf4 magnitude3_sq(vf4 v) noexcept
{
	return dot3(v, v);
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

[[nodiscard]] TNVX_INLINE
vf4 max(vf4 l, vf4 r) noexcept
{
	return _mm_max_ps(l, r);
}

[[nodiscard]] TNVX_INLINE
vf4 min(vf4 l, vf4 r) noexcept
{
	return _mm_min_ps(l, r);
}

[[nodiscard]] TNVX_INLINE
vf4 floor(vf4 v) noexcept
{
	return _mm_floor_ps(v);
}

[[nodiscard]] TNVX_INLINE
vf4 round(vf4 v) noexcept
{
	return _mm_round_ps(v, _MM_FROUND_TO_NEAREST_INT | _MM_FROUND_NO_EXC);
}

[[nodiscard]] TNVX_INLINE
vf4 ceil(vf4 v) noexcept
{
	return _mm_ceil_ps(v);
}

[[nodiscard]] TNVX_INLINE
vf4 frac(vf4 v) noexcept
{
	return _mm_sub_ps(v, _mm_floor_ps(v));
}

}
