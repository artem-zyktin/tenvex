#pragma once

#include "config.h"
#include "defines.h"

#if defined(TNVX_NEON)
#include <arm_neon.h>
using vf4 = float32x4_t;
#else
#error "tenvex requires NEON backend"
#endif

struct mf4 { vf4 cols[4]; };

#if defined(TNVX_NEON)

namespace tnvx::detail
{

[[nodiscard]] TNVX_INLINE
vf4 set(float a, float b, float c, float d)
{
	const float tmp[4] = { a, b, c, d };
	return vld1q_f32(tmp);
}

[[nodiscard]] TNVX_INLINE
vf4 set_all(float a)
{
	return vdupq_n_f32(a);
}

[[nodiscard]] TNVX_INLINE
vf4 abs(vf4 v)
{
	return vabsq_f32(v);
}

[[nodiscard]] TNVX_INLINE
float to_float(vf4 v)
{
	return vgetq_lane_f32(v, 0);
}

[[nodiscard]] TNVX_INLINE
bool eq(vf4 a, vf4 b)
{
	const uint32x4_t mask = vceqq_f32(a, b);
	return vminvq_u32(mask) == 0xFFFFFFFFu;
}

[[nodiscard]] TNVX_INLINE
bool approx_eq(vf4 a, vf4 b, float eps) noexcept
{
	const float32x4_t diff = vabsq_f32(vsubq_f32(a, b));
	const uint32x4_t mask = vcleq_f32(diff, vdupq_n_f32(eps));
	return vminvq_u32(mask) == 0xFFFFFFFFu;
}

[[nodiscard]] TNVX_INLINE
vf4 scalar(float value) noexcept
{
	return vdupq_n_f32(value);
}

template<int lane>
[[nodiscard]] TNVX_INLINE
float get_lane(vf4 v) noexcept
{
	return vgetq_lane_f32(v, lane);
}

[[nodiscard]] TNVX_INLINE
vf4 neg(vf4 v) noexcept
{
	return vnegq_f32(v);
}

[[nodiscard]] TNVX_INLINE vf4 conjugate(vf4 q) noexcept
{
	const uint32_t m[4] = { 0x80000000u, 0x80000000u, 0x80000000u, 0x00000000u };
	return vreinterpretq_f32_u32(veorq_u32(vreinterpretq_u32_f32(q), vld1q_u32(m)));
}

[[nodiscard]] TNVX_INLINE
vf4 add(vf4 l, vf4 r) noexcept
{
	return vaddq_f32(l, r);
}

[[nodiscard]] TNVX_INLINE
vf4 sub(vf4 l, vf4 r) noexcept
{
	return vsubq_f32(l, r);
}

[[nodiscard]] TNVX_INLINE
vf4 mul(vf4 l, vf4 r) noexcept
{
	return vmulq_f32(l, r);
}

[[nodiscard]] TNVX_INLINE
vf4 div(vf4 l, vf4 r) noexcept
{
	return vdivq_f32(l, r);
}

[[nodiscard]] TNVX_INLINE
vf4 dot3(vf4 l, vf4 r) noexcept
{
	float32x4_t prod = vmulq_f32(l, r);
	prod = vsetq_lane_f32(0.0f, prod, 3);
	const float s = vaddvq_f32(prod);
	return vdupq_n_f32(s);
}

[[nodiscard]] TNVX_INLINE
vf4 dot4(vf4 l, vf4 r) noexcept
{
	const float s = vaddvq_f32(vmulq_f32(l, r));
	return vdupq_n_f32(s);
}

[[nodiscard]] TNVX_INLINE
vf4 magnitude3(vf4 v) noexcept
{
	return vsqrtq_f32(dot3(v, v));
}

[[nodiscard]] TNVX_INLINE
vf4 magnitude3_sq(vf4 v) noexcept
{
	return dot3(v, v);
}

[[nodiscard]] TNVX_INLINE
vf4 magnitude4(vf4 v) noexcept
{
	return vsqrtq_f32(dot4(v, v));
}

[[nodiscard]] TNVX_INLINE
vf4 magnitude4_sq(vf4 v) noexcept
{
	return dot4(v, v);
}

[[nodiscard]] TNVX_INLINE
vf4 normalize3(vf4 v) noexcept
{
	const float32x4_t n = vdivq_f32(v, magnitude3(v));
	return vsetq_lane_f32(vgetq_lane_f32(v, 3), n, 3);
}

[[nodiscard]] TNVX_INLINE
vf4 cross3(vf4 l, vf4 r) noexcept
{
	alignas(16) static const uint8_t idx_yzx_bytes[16] = {
		4, 5, 6, 7,    8, 9,10,11,    0, 1, 2, 3,   12,13,14,15
	};
	alignas(16) static const uint8_t idx_zxy_bytes[16] = {
		8, 9,10,11,    0, 1, 2, 3,    4, 5, 6, 7,   12,13,14,15
	};
	const uint8x16_t idx_yzx = vld1q_u8(idx_yzx_bytes);
	const uint8x16_t idx_zxy = vld1q_u8(idx_zxy_bytes);

	const uint8x16_t lb = vreinterpretq_u8_f32(l);
	const uint8x16_t rb = vreinterpretq_u8_f32(r);

	const float32x4_t l_yzx = vreinterpretq_f32_u8(vqtbl1q_u8(lb, idx_yzx));
	const float32x4_t r_zxy = vreinterpretq_f32_u8(vqtbl1q_u8(rb, idx_zxy));
	const float32x4_t l_zxy = vreinterpretq_f32_u8(vqtbl1q_u8(lb, idx_zxy));
	const float32x4_t r_yzx = vreinterpretq_f32_u8(vqtbl1q_u8(rb, idx_yzx));

	return vsubq_f32(vmulq_f32(l_yzx, r_zxy), vmulq_f32(l_zxy, r_yzx));
}

[[nodiscard]] TNVX_INLINE
vf4 max(vf4 l, vf4 r) noexcept
{
	return vmaxq_f32(l, r);
}

[[nodiscard]] TNVX_INLINE
vf4 min(vf4 l, vf4 r) noexcept
{
	return vminq_f32(l, r);
}

[[nodiscard]] TNVX_INLINE
vf4 floor(vf4 v) noexcept
{
	return vrndmq_f32(v);
}

[[nodiscard]] TNVX_INLINE
vf4 round(vf4 v) noexcept
{
	return vrndnq_f32(v);
}

[[nodiscard]] TNVX_INLINE
vf4 ceil(vf4 v) noexcept
{
	return vrndpq_f32(v);
}

[[nodiscard]] TNVX_INLINE
vf4 frac(vf4 v) noexcept
{
	return vsubq_f32(v, vrndmq_f32(v));
}

[[nodiscard]] TNVX_INLINE
vf4 rsqrt(vf4 x) noexcept
{
	// 1/sqrt(x) estimate refined by one Newton-Raphson step:
	// y1 = y0 * (1.5 - 0.5*x*y0*y0)
	float32x4_t y0 = vrsqrteq_f32(x);
	y0 = vmulq_f32(y0, vrsqrtsq_f32(vmulq_f32(x, y0), y0));
	return y0;
}

[[nodiscard]] TNVX_INLINE
vf4 normalize3_fast(vf4 v) noexcept
{
	const float32x4_t inv_len = rsqrt(dot3(v, v));
	const float32x4_t n = vmulq_f32(v, inv_len);
	return vsetq_lane_f32(vgetq_lane_f32(v, 3), n, 3);
}

[[nodiscard]] TNVX_INLINE
vf4 with_w(vf4 xyz_source, vf4 w_source)
{
	return vcopyq_laneq_f32(xyz_source, 3, w_source, 3);
}

[[nodiscard]] TNVX_INLINE
vf4 quat_mul(vf4 a, vf4 b) noexcept
{
	const vf4 aw = vdupq_laneq_f32(a, 3);
	const vf4 ax = vdupq_laneq_f32(a, 0);
	const vf4 ay = vdupq_laneq_f32(a, 1);
	const vf4 az = vdupq_laneq_f32(a, 2);

	const vf4 b3 = vrev64q_f32(b);     // (by,bx,bw,bz)
	const vf4 b2 = vextq_f32(b, b, 2); // (bz,bw,bx,by)
	const vf4 b1 = vrev64q_f32(b2);    // (bw,bz,by,bx)

	const uint32_t m1[4] = { 0x0, 0x80000000, 0x0, 0x80000000 }; // (+,-,+,-)
	const uint32_t m2[4] = { 0x0, 0x0, 0x80000000, 0x80000000 }; // (+,+,-,-)
	const uint32_t m3[4] = { 0x80000000, 0x0, 0x0, 0x80000000 }; // (-,+,+,-)

	const vf4 t0 = vmulq_f32(aw, b);
	const vf4 t1 = vreinterpretq_f32_u32(veorq_u32(vreinterpretq_u32_f32(vmulq_f32(ax, b1)), vld1q_u32(m1)));
	const vf4 t2 = vreinterpretq_f32_u32(veorq_u32(vreinterpretq_u32_f32(vmulq_f32(ay, b2)), vld1q_u32(m2)));
	const vf4 t3 = vreinterpretq_f32_u32(veorq_u32(vreinterpretq_u32_f32(vmulq_f32(az, b3)), vld1q_u32(m3)));

	return vaddq_f32(vaddq_f32(t0, t1), vaddq_f32(t2, t3));
}

[[nodiscard]] TNVX_INLINE
vf4 rotate(vf4 v, vf4 q) noexcept
{
	// v' = v + 2w(n x v) + 2(n x (n x v)),  n = q.xyz, w = q.w.  q must be unit
	const vf4 c1 = cross3(q, v);
	const vf4 c2 = cross3(q, c1);
	const vf4 wq = vdupq_laneq_f32(q, 3);
	const vf4 two = vdupq_n_f32(2.0f);
	const vf4 t1 = mul(mul(two, wq), c1);
	const vf4 t2 = mul(two, c2);
	return add(v, add(t1, t2));
}

[[nodiscard]] TNVX_INLINE
vf4 inverse(vf4 q) noexcept
{
	return vdivq_f32(conjugate(q), magnitude4_sq(q));
}

[[nodiscard]] TNVX_INLINE
vf4 normalize4(vf4 q) noexcept
{
	return vdivq_f32(q, magnitude4(q));
}

[[nodiscard]] TNVX_INLINE
mf4 mat_from_quat(vf4 q) noexcept
{
	alignas(16) static const uint8_t idx_yxx_bytes[16] = {
		4, 5, 6, 7,    0, 1, 2, 3,    0, 1, 2, 3,   12,13,14,15
	};
	alignas(16) static const uint8_t idx_zzy_bytes[16] = {
		8, 9,10,11,    8, 9,10,11,    4, 5, 6, 7,   12,13,14,15
	};
	alignas(16) static const uint8_t idx_yzx_bytes[16] = {
		4, 5, 6, 7,    8, 9,10,11,    0, 1, 2, 3,   12,13,14,15
	};
	alignas(16) static const uint8_t idx_zxy_bytes[16] = {
		8, 9,10,11,    0, 1, 2, 3,    4, 5, 6, 7,   12,13,14,15
	};

	const uint8x16_t idx_yxx = vld1q_u8(idx_yxx_bytes);
	const uint8x16_t idx_zzy = vld1q_u8(idx_zzy_bytes);
	const uint8x16_t idx_yzx = vld1q_u8(idx_yzx_bytes);
	const uint8x16_t idx_zxy = vld1q_u8(idx_zxy_bytes);

	const vf4 q2 = vaddq_f32(q, q);
	const vf4 e  = vmulq_f32(q, q2);

	const uint8x16_t eb  = vreinterpretq_u8_f32(e);
	const vf4 e1 = vreinterpretq_f32_u8(vqtbl1q_u8(eb, idx_yxx));
	const vf4 e2 = vreinterpretq_f32_u8(vqtbl1q_u8(eb, idx_zzy));

	vf4 dg = vsubq_f32(vsubq_f32(set(1.0f, 1.0f, 1.0f, 0.0f), e1), e2);
	dg = vsetq_lane_f32(0.0f, dg, 3);

	const vf4 q_yzx  = vreinterpretq_f32_u8(vqtbl1q_u8(vreinterpretq_u8_f32(q),  idx_yzx));
	const vf4 q2_zxy = vreinterpretq_f32_u8(vqtbl1q_u8(vreinterpretq_u8_f32(q2), idx_zxy));

	const vf4 p = vmulq_f32(q_yzx, q2);
	const vf4 w = vmulq_f32(q2_zxy, vdupq_laneq_f32(q, 3));

	const vf4 s  = vaddq_f32(p, w);
	const vf4 sr = vreinterpretq_f32_u8(vqtbl1q_u8(vreinterpretq_u8_f32(s), idx_zxy));
	const vf4 m  = vsubq_f32(p, w);

	mf4 r;
	r.cols[0] = vcopyq_laneq_f32(vcopyq_laneq_f32(dg, 1, sr, 1), 2, m,  2);
	r.cols[1] = vcopyq_laneq_f32(vcopyq_laneq_f32(dg, 0, m,  0), 2, sr, 2);
	r.cols[2] = vcopyq_laneq_f32(vcopyq_laneq_f32(dg, 0, sr, 0), 1, m,  1);
	r.cols[3] = set(0.0f, 0.0f, 0.0f, 1.0f);

	return r;
}

// Matrix kernels. The element-wise four are overloads rather than mat_-prefixed
// names like mat_from_quat above: the shared Add / Sub / Neg / Mul nodes
// dispatch on the operand type, so the matrix case has to answer to the same
// name as the vf4 case.

[[nodiscard]] TNVX_INLINE
mf4 add(mf4 a, mf4 b) noexcept
{
	mf4 r;
	r.cols[0] = vaddq_f32(a.cols[0], b.cols[0]);
	r.cols[1] = vaddq_f32(a.cols[1], b.cols[1]);
	r.cols[2] = vaddq_f32(a.cols[2], b.cols[2]);
	r.cols[3] = vaddq_f32(a.cols[3], b.cols[3]);

	return r;
}

[[nodiscard]] TNVX_INLINE
mf4 sub(mf4 a, mf4 b) noexcept
{
	mf4 r;
	r.cols[0] = vsubq_f32(a.cols[0], b.cols[0]);
	r.cols[1] = vsubq_f32(a.cols[1], b.cols[1]);
	r.cols[2] = vsubq_f32(a.cols[2], b.cols[2]);
	r.cols[3] = vsubq_f32(a.cols[3], b.cols[3]);

	return r;
}

[[nodiscard]] TNVX_INLINE
mf4 neg(mf4 m) noexcept
{
	mf4 r;
	r.cols[0] = vnegq_f32(m.cols[0]);
	r.cols[1] = vnegq_f32(m.cols[1]);
	r.cols[2] = vnegq_f32(m.cols[2]);
	r.cols[3] = vnegq_f32(m.cols[3]);

	return r;
}

[[nodiscard]] TNVX_INLINE
mf4 mul(mf4 m, vf4 s) noexcept
{
	mf4 r;
	r.cols[0] = vmulq_f32(m.cols[0], s);
	r.cols[1] = vmulq_f32(m.cols[1], s);
	r.cols[2] = vmulq_f32(m.cols[2], s);
	r.cols[3] = vmulq_f32(m.cols[3], s);

	return r;
}

[[nodiscard]] TNVX_INLINE
mf4 mul(vf4 s, mf4 m) noexcept
{
	return mul(m, s);
}

[[nodiscard]] TNVX_INLINE
mf4 mat_transpose(mf4 m) noexcept
{
	const float32x4x2_t t01 = vtrnq_f32(m.cols[0], m.cols[1]);
	const float32x4x2_t t23 = vtrnq_f32(m.cols[2], m.cols[3]);

	mf4 r;
	r.cols[0] = vcombine_f32(vget_low_f32(t01.val[0]), vget_low_f32(t23.val[0]));
	r.cols[1] = vcombine_f32(vget_low_f32(t01.val[1]), vget_low_f32(t23.val[1]));
	r.cols[2] = vcombine_f32(vget_high_f32(t01.val[0]), vget_high_f32(t23.val[0]));
	r.cols[3] = vcombine_f32(vget_high_f32(t01.val[1]), vget_high_f32(t23.val[1]));

	return r;
}

[[nodiscard]] TNVX_INLINE
vf4 mat_transform(vf4 v, mf4 m) noexcept
{
	// linear combination of the columns - 4 broadcasts + 4 multiply-adds,
	// no shuffle of the matrix and no horizontal reduction. This is the
	// kernel the column-major layout is chosen for; here the broadcast
	// folds into fmla by lane.
	vf4 r = vmulq_laneq_f32(m.cols[0], v, 0);
	r = vfmaq_laneq_f32(r, m.cols[1], v, 1);
	r = vfmaq_laneq_f32(r, m.cols[2], v, 2);
	r = vfmaq_laneq_f32(r, m.cols[3], v, 3);

	return r;
}

[[nodiscard]] TNVX_INLINE
mf4 mat_mul(mf4 a, mf4 b) noexcept
{
	mf4 r;
	r.cols[0] = mat_transform(b.cols[0], a);
	r.cols[1] = mat_transform(b.cols[1], a);
	r.cols[2] = mat_transform(b.cols[2], a);
	r.cols[3] = mat_transform(b.cols[3], a);

	return r;
}

[[nodiscard]] TNVX_INLINE
vf4 mat_determinant(mf4 m) noexcept
{
	// cofactor form over the xyz parts a,b,c,d of the four columns and the
	// w lanes x,y,z,w that make up row 3:
	//   det = (a x b) . (c*w - d*z) + (c x d) . (a*y - b*x)
	const vf4 a = m.cols[0];
	const vf4 b = m.cols[1];
	const vf4 c = m.cols[2];
	const vf4 d = m.cols[3];

	const vf4 x = vdupq_laneq_f32(a, 3);
	const vf4 y = vdupq_laneq_f32(b, 3);
	const vf4 z = vdupq_laneq_f32(c, 3);
	const vf4 w = vdupq_laneq_f32(d, 3);

	const vf4 s = cross3(a, b);
	const vf4 t = cross3(c, d);
	const vf4 u = vsubq_f32(vmulq_f32(a, y), vmulq_f32(b, x));
	const vf4 v = vsubq_f32(vmulq_f32(c, w), vmulq_f32(d, z));

	return vaddq_f32(dot3(s, v), dot3(t, u));
}

[[nodiscard]] TNVX_INLINE
mf4 mat_inverse(mf4 m) noexcept
{
	// the decomposition of mat_determinant carried on to the adjugate.
	// rows.cols[i] is ROW i of the inverse, so the assembly is transposed
	// back into columns at the end. A singular matrix divides by zero and
	// yields inf / nan lanes, as normalize3 does for a zero vector - the
	// precondition is not checked.
	const vf4 a = m.cols[0];
	const vf4 b = m.cols[1];
	const vf4 c = m.cols[2];
	const vf4 d = m.cols[3];

	const vf4 x = vdupq_laneq_f32(a, 3);
	const vf4 y = vdupq_laneq_f32(b, 3);
	const vf4 z = vdupq_laneq_f32(c, 3);
	const vf4 w = vdupq_laneq_f32(d, 3);

	vf4 s = cross3(a, b);
	vf4 t = cross3(c, d);
	vf4 u = vsubq_f32(vmulq_f32(a, y), vmulq_f32(b, x));
	vf4 v = vsubq_f32(vmulq_f32(c, w), vmulq_f32(d, z));

	const vf4 inv_det = vdivq_f32(vdupq_n_f32(1.0f),
								  vaddq_f32(dot3(s, v), dot3(t, u)));
	s = vmulq_f32(s, inv_det);
	t = vmulq_f32(t, inv_det);
	u = vmulq_f32(u, inv_det);
	v = vmulq_f32(v, inv_det);

	mf4 rows;
	rows.cols[0] = with_w(vaddq_f32(cross3(b, v), vmulq_f32(t, y)), neg(dot3(b, t)));
	rows.cols[1] = with_w(vsubq_f32(cross3(v, a), vmulq_f32(t, x)),     dot3(a, t));
	rows.cols[2] = with_w(vaddq_f32(cross3(d, u), vmulq_f32(s, w)), neg(dot3(d, s)));
	rows.cols[3] = with_w(vsubq_f32(cross3(u, c), vmulq_f32(s, z)),     dot3(c, s));

	return mat_transpose(rows);
}

}

#endif
