#include "codegen.h"

// Compound expression: normalize3(a + b*2) * dot3(b, c) + c*3, loop-shaped
// over arrays (the GCC/AArch64 dead-store defect reproduces only under this
// access pattern - array-indexed leaves, vb/vc used twice, captured by
// value).
//
// Invariant: the loop body of _et matches _manual up to register allocation
// (known exception: GCC/AArch64 materializes the expression object - dead
// stores, see README "Is the abstraction zero-cost?").
// _intrin is an independent hand-written reference; comparable in quality,
// not instruction-identical (e.g. it may pick dpps where the kernels use
// mul+shuffles).

TNVX_CODEGEN void cg_compound_et(const vec4* va, const vec4* vb, const vec4* vc,
                                 vf4* out, std::size_t n)
{
	for (std::size_t i = 0; i < n; ++i)
		out[i] = (normalize3(va[i] + vb[i] * 2.0f) * dot3(vb[i], vc[i])
		          + vc[i] * 3.0f).eval();
}

// value shape: everything arrives in registers - the cleanest view of the
// fused expression (loads/stores belong to the loop shapes, not here)
TNVX_CODEGEN vf4 cg_compound_value(const vec4& a, const vec4& b, const vec4& c)
{
	return (normalize3(a + b * 2.0f) * dot3(b, c) + c * 3.0f).eval();
}

TNVX_CODEGEN void cg_compound_manual(const vec4* va, const vec4* vb, const vec4* vc,
                                     vf4* out, std::size_t n)
{
	using namespace tnvx::detail;

	for (std::size_t i = 0; i < n; ++i)
	{
		vf4 a = va[i].eval(),
		    b = vb[i].eval(),
		    c = vc[i].eval();

		vf4 t = normalize3(add(a, mul(b, set_all(2.0f))));
		vf4 d = dot3(b, c);
		out[i] = add(mul(t, d), mul(c, set_all(3.0f)));
	}
}

#if defined(TNVX_SSE41)

static TNVX_INLINE __m128 dp3_raw(__m128 a, __m128 b)
{
	return _mm_dp_ps(a, b, 0x7F);
}

static TNVX_INLINE __m128 norm3_raw(__m128 v)
{
	__m128 len = _mm_sqrt_ps(dp3_raw(v, v));
	return _mm_blend_ps(_mm_div_ps(v, len), v, 0b1000);
}

TNVX_CODEGEN void cg_compound_intrin(const vec4* va, const vec4* vb, const vec4* vc,
                                     vf4* out, std::size_t n)
{
	for (std::size_t i = 0; i < n; ++i)
	{
		__m128 a = va[i].eval(), b = vb[i].eval(), c = vc[i].eval();
		__m128 t = norm3_raw(_mm_add_ps(a, _mm_mul_ps(b, _mm_set1_ps(2.0f))));
		__m128 d = dp3_raw(b, c);
		out[i] = _mm_add_ps(_mm_mul_ps(t, d), _mm_mul_ps(c, _mm_set1_ps(3.0f)));
	}
}

#elif defined(TNVX_NEON)

static TNVX_INLINE float32x4_t dp3_raw(float32x4_t a, float32x4_t b)
{
	float32x4_t prod = vmulq_f32(a, b);
	prod = vsetq_lane_f32(0.0f, prod, 3);
	return vdupq_n_f32(vaddvq_f32(prod));
}

static TNVX_INLINE float32x4_t norm3_raw(float32x4_t v)
{
	float32x4_t len = vsqrtq_f32(dp3_raw(v, v));
	float32x4_t nrm = vdivq_f32(v, len);
	return vsetq_lane_f32(vgetq_lane_f32(v, 3), nrm, 3);
}

TNVX_CODEGEN void cg_compound_intrin(const vec4* va, const vec4* vb, const vec4* vc,
                                     vf4* out, std::size_t n)
{
	for (std::size_t i = 0; i < n; ++i)
	{
		float32x4_t a = va[i].eval(), b = vb[i].eval(), c = vc[i].eval();
		float32x4_t t = norm3_raw(vaddq_f32(a, vmulq_f32(b, vdupq_n_f32(2.0f))));
		float32x4_t d = dp3_raw(b, c);
		out[i] = vaddq_f32(vmulq_f32(t, d), vmulq_f32(c, vdupq_n_f32(3.0f)));
	}
}

#endif
