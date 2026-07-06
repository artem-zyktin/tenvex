#pragma once

#include "config.h"
#include "defines.h"

#if defined(TNVX_SSE41)
#include <smmintrin.h>
using vf4 = __m128;
#else
#error "tenvex requires SSE4.1 backend"
#endif

#if defined(TNVX_SSE41)

namespace tnvx::detail
{

[[nodiscard]] TNVX_INLINE
vf4 set(float a, float b, float c, float d)
{
	return _mm_set_ps(d, c, b, a);
}

[[nodiscard]] TNVX_INLINE
vf4 set_all(float a)
{
	return _mm_set1_ps(a);
}

[[nodiscard]] TNVX_INLINE
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
	if constexpr (lane == 0)
	{
		return _mm_cvtss_f32(v);
	}
	else
	{
		return _mm_cvtss_f32(_mm_shuffle_ps(v, v, _MM_SHUFFLE(0, 0, 0, lane)));
	}
}

[[nodiscard]] TNVX_INLINE
vf4 neg(vf4 v) noexcept
{
	return _mm_xor_ps(v, _mm_set1_ps(-0.0f));
}

[[nodiscard]] TNVX_INLINE vf4 conjugate(vf4 q) noexcept
{
	return _mm_xor_ps(q, _mm_set_ps(0.0f, -0.0f, -0.0f, -0.0f));
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
	vf4 t = _mm_mul_ps(l, r);
	vf4 ty = _mm_shuffle_ps(t, t, _MM_SHUFFLE(1, 1, 1, 1));
	vf4 xy = _mm_add_ss(t, ty);
	vf4 tz = _mm_movehl_ps(t, t);
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
vf4 magnitude4(vf4 v) noexcept
{
	return _mm_sqrt_ps(dot4(v, v));
}

[[nodiscard]] TNVX_INLINE
vf4 magnitude4_sq(vf4 v) noexcept
{
	return dot4(v, v);
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

[[nodiscard]] TNVX_INLINE
vf4 rsqrt(vf4 x) noexcept
{
	// 1/sqrt(x) estimate refined by one Newton-Raphson step:
	// y1 = y0 * (1.5 - 0.5*x*y0*y0)
	const vf4 y0 = _mm_rsqrt_ps(x);
	const vf4 y0sq = _mm_mul_ps(y0, y0);
	const vf4 t = _mm_sub_ps(_mm_set1_ps(1.5f),
							 _mm_mul_ps(_mm_mul_ps(_mm_set1_ps(0.5f), x), y0sq));
	return _mm_mul_ps(y0, t);
}

[[nodiscard]] TNVX_INLINE
vf4 norm3_fast(vf4 v) noexcept
{
	const vf4 inv_len = rsqrt(dot3(v, v));
	return _mm_blend_ps(_mm_mul_ps(v, inv_len), v, 0b1000);
}

[[nodiscard]] TNVX_INLINE
vf4 with_w(vf4 xyz_source, vf4 w_source)
{
	return _mm_blend_ps(xyz_source, w_source, 0b1000);
}

[[nodiscard]] TNVX_INLINE
vf4 quat_mul(vf4 a, vf4 b) noexcept
{
	const vf4 aw = _mm_shuffle_ps(a, a, _MM_SHUFFLE(3, 3, 3, 3));
	const vf4 ax = _mm_shuffle_ps(a, a, _MM_SHUFFLE(0, 0, 0, 0));
	const vf4 ay = _mm_shuffle_ps(a, a, _MM_SHUFFLE(1, 1, 1, 1));
	const vf4 az = _mm_shuffle_ps(a, a, _MM_SHUFFLE(2, 2, 2, 2));

	const vf4 b1 = _mm_shuffle_ps(b, b, _MM_SHUFFLE(0, 1, 2, 3)); // (bw,bz,by,bx)
	const vf4 b2 = _mm_shuffle_ps(b, b, _MM_SHUFFLE(1, 0, 3, 2)); // (bz,bw,bx,by)
	const vf4 b3 = _mm_shuffle_ps(b, b, _MM_SHUFFLE(2, 3, 0, 1)); // (by,bx,bw,bz)

	const vf4 s1 = _mm_set_ps(-0.0f, 0.0f, -0.0f, 0.0f); // (+,-,+,-)
	const vf4 s2 = _mm_set_ps(-0.0f, -0.0f, 0.0f, 0.0f); // (+,+,-,-)
	const vf4 s3 = _mm_set_ps(-0.0f, 0.0f, 0.0f, -0.0f); // (-,+,+,-)

	const vf4 t0 = _mm_mul_ps(aw, b);
	const vf4 t1 = _mm_xor_ps(_mm_mul_ps(ax, b1), s1);
	const vf4 t2 = _mm_xor_ps(_mm_mul_ps(ay, b2), s2);
	const vf4 t3 = _mm_xor_ps(_mm_mul_ps(az, b3), s3);

	return _mm_add_ps(_mm_add_ps(t0, t1), _mm_add_ps(t2, t3));
}

[[nodiscard]] TNVX_INLINE
vf4 rotate(vf4 v, vf4 q) noexcept
{
	// v' = v + 2w(n x v) + 2(n x (n x v)),  n = q.xyz, w = q.w.  q must be unit
	const vf4 c1 = cross3(q, v);
	const vf4 c2 = cross3(q, c1);
	const vf4 wq = _mm_shuffle_ps(q, q, _MM_SHUFFLE(3, 3, 3, 3));
	const vf4 two = _mm_set1_ps(2.0f);
	const vf4 t1 = mul(mul(two, wq), c1);
	const vf4 t2 = mul(two, c2);
	return add(v, add(t1, t2));
}

[[nodiscard]] TNVX_INLINE
vf4 inverse(vf4 q) noexcept
{
	return _mm_div_ps(conjugate(q), magnitude4_sq(q));
}

[[nodiscard]] TNVX_INLINE
vf4 normalize(vf4 q) noexcept
{
	return _mm_div_ps(q, magnitude4(q));
}

} // namespace tnvx::detail

#endif
