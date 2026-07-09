#include "codegen.h"

// Composed eager operations (free functions returning concrete vec4/quat).
// They are built from the same nodes, so the question here is whether the
// eager boundary costs anything: the temporaries must dissolve and the body
// must look hand-fused.
//
// What to look for:
// - cg_lerp: a + (b-a)*t -> sub + fma (or sub+mul+add), t broadcast hoisted.
// - cg_clamp: exactly min + max.
// - cg_reflect: dot3 + one fused multiply-subtract chain.
// - cg_distance3_sq: sub + dot3, NO sqrt (the _sq form exists to skip it).
// - cg_orthogonal: branchless lane select expected - watch for actual
//   branches in the body.
// - cg_nlerp: sign flip (shortest arc) + lerp + normalize4; one sqrt, one
//   div, no calls into libm (unlike slerp, which is deliberately not probed:
//   acos/sin calls dominate and there is nothing to see).

TNVX_CODEGEN void cg_lerp(const vec4* va, const vec4* vb, float t,
                          vf4* out, std::size_t n)
{
	for (std::size_t i = 0; i < n; ++i)
		out[i] = lerp(va[i], vb[i], t).eval();
}

TNVX_CODEGEN void cg_clamp(const vec4* va, const vec4* vlo, const vec4* vhi,
                           vf4* out, std::size_t n)
{
	for (std::size_t i = 0; i < n; ++i)
		out[i] = clamp(va[i], vlo[i], vhi[i]).eval();
}

TNVX_CODEGEN void cg_reflect(const vec4* va, const vec4* vn,
                             vf4* out, std::size_t n)
{
	for (std::size_t i = 0; i < n; ++i)
		out[i] = reflect(va[i], vn[i]).eval();
}

TNVX_CODEGEN void cg_distance3_sq(const vec4* va, const vec4* vb,
                                  float* out, std::size_t n)
{
	for (std::size_t i = 0; i < n; ++i)
		out[i] = distance3_sq(va[i], vb[i]);
}

TNVX_CODEGEN void cg_orthogonal(const vec4* va, vf4* out, std::size_t n)
{
	for (std::size_t i = 0; i < n; ++i)
		out[i] = orthogonal(va[i]).eval();
}

TNVX_CODEGEN void cg_nlerp(const quat* qa, const quat* qb, float t,
                           vf4* out, std::size_t n)
{
	for (std::size_t i = 0; i < n; ++i)
		out[i] = nlerp(qa[i], qb[i], t).eval();
}
