#include "codegen.h"

// Quaternion nodes.
//
// What to look for:
// - cg_hamilton: shuffles + mul + sign-flip xor + add, no stack traffic.
// - cg_rotate: two cross products; the w lane of v carried through.
// - cg_conj_scale: conjugate is one xor (sign mask on xyz); it must fuse
//   with the scalar multiply - two arithmetic ops total in the body.
// - cg_rotate_fused: rotate is a vec_expr - it must fuse into the larger
//   vector expression with no boundary (no extra moves between the rotate
//   result and the add/scale).
// - cg_quat_inverse: conjugate + dot4 + div, no sqrt (inverse divides by
//   the squared magnitude).
// _value probes are the bare kernels without loop scaffolding - clean
// reference listings.

TNVX_CODEGEN void cg_hamilton(const quat* qa, const quat* qb,
                              vf4* out, std::size_t n)
{
	for (std::size_t i = 0; i < n; ++i)
		out[i] = (qa[i] * qb[i]).eval();
}

TNVX_CODEGEN void cg_rotate(const vec4* va, const quat* qa,
                            vf4* out, std::size_t n)
{
	for (std::size_t i = 0; i < n; ++i)
		out[i] = rotate(va[i], qa[i]).eval();
}

TNVX_CODEGEN void cg_conj_scale(const quat* qa, vf4* out, std::size_t n)
{
	for (std::size_t i = 0; i < n; ++i)
		out[i] = (conjugate(qa[i]) * 2.0f).eval();
}

TNVX_CODEGEN void cg_quat_inverse(const quat* qa, vf4* out, std::size_t n)
{
	for (std::size_t i = 0; i < n; ++i)
		out[i] = inverse(qa[i]).eval();
}

TNVX_CODEGEN void cg_rotate_fused(const vec4* va, const vec4* vb, const quat* qa,
                                  vf4* out, std::size_t n)
{
	for (std::size_t i = 0; i < n; ++i)
		out[i] = (rotate(va[i], qa[i]) + vb[i] * 2.0f).eval();
}

TNVX_CODEGEN vf4 cg_hamilton_value(const quat& a, const quat& b)
{
	return (a * b).eval();
}

TNVX_CODEGEN vf4 cg_rotate_value(const vec4& v, const quat& q)
{
	return rotate(v, q).eval();
}
