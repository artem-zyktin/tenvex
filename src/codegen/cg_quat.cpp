#include "codegen.h"

// Quaternion nodes.
//
// What to look for:
// - cg_hamilton: shuffles + mul + sign-flip xor + add, no stack traffic.
// - cg_rotate: two cross products; the w lane of v carried through.
// - cg_conj_scale: conjugate is one xor (sign mask on xyz); it must fuse
//   with the scalar multiply - two arithmetic ops total in the body.
// - cg_quat_inverse: conjugate + dot4 + div, no sqrt (inverse divides by
//   the squared magnitude).

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
