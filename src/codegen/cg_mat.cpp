#include "codegen.h"

// Matrix factories.
//
// Reading note: mf4 is 64 bytes, so every _value probe returns through a
// hidden pointer (sret). Four stores in those listings are ABI, not the
// kernel - judge stack traffic by the loop probes, and use _value only to
// read the arithmetic.
//
// What to look for:
// - cg_mat_from_quat: ~20 ops, all in registers. One add, three muls,
//   four shuffles, six blends, two constants from the pool. No spills.
// - cg_mat_scaling_scalar: the benchmark's biggest loss on MSVC (2.73 vs
//   1.50 ns naive). Three runtime floats into a 64-byte result should be
//   three inserts into zeroed registers. If the arguments instead go to
//   the stack and come back, the cost is in the 16-scalar constructor,
//   not in scaling - and zero / identity / scaling(float) pay it too.
// - cg_mat_identity: all-constant arguments through that same
//   constructor. Must fold to four pool loads; if it doesn't, the
//   constructor is the problem regardless of runtime inputs.
// - cg_mat_translation: three columns constant, one blend. Naive won this
//   benchmark too; the listing should show whether the constant columns
//   are loaded once outside the loop or rebuilt per iteration.
// - cg_mat_scaling_vec: three hadamards against unit_x / unit_y / unit_z.
//   Compare against cg_mat_scaling_scalar - same matrix, other route.
// - cg_mat_at: one indexed column load plus a lane extract (shufps +
//   movss on SSE, umov on NEON). This is the listing that justifies the
//   "slow, not for hot paths" warning in the docs.

TNVX_CODEGEN void cg_mat_from_quat(const quat* qa, mf4* out, std::size_t n)
{
	for (std::size_t i = 0; i < n; ++i)
		out[i] = mat4::from_quat(qa[i]).eval();
}

TNVX_CODEGEN void cg_mat_translation(const vec4* va, mf4* out, std::size_t n)
{
	for (std::size_t i = 0; i < n; ++i)
		out[i] = mat4::translation(va[i]).eval();
}

TNVX_CODEGEN void cg_mat_scaling_vec(const vec4* va, mf4* out, std::size_t n)
{
	for (std::size_t i = 0; i < n; ++i)
		out[i] = mat4::scaling(va[i]).eval();
}

TNVX_CODEGEN void cg_mat_scaling_scalar(const float* sx, const float* sy,
                                        const float* sz, mf4* out, std::size_t n)
{
	for (std::size_t i = 0; i < n; ++i)
		out[i] = mat4::scaling(sx[i], sy[i], sz[i]).eval();
}

TNVX_CODEGEN void cg_mat_identity(mf4* out, std::size_t n)
{
	for (std::size_t i = 0; i < n; ++i)
		out[i] = mat4::identity().eval();
}

TNVX_CODEGEN void cg_mat_at(const mat4* ma, float* out, std::size_t n)
{
	for (std::size_t i = 0; i < n; ++i)
		out[i] = ma[i].at<2, 1>();
}

TNVX_CODEGEN void cg_mat_col(const mat4* ma, vf4* out, std::size_t n)
{
	for (std::size_t i = 0; i < n; ++i)
		out[i] = ma[i].col(1).eval();
}

TNVX_CODEGEN mf4 cg_mat_from_quat_value(const quat& q)
{
	return mat4::from_quat(q).eval();
}

TNVX_CODEGEN mf4 cg_mat_translation_value(const vec4& t)
{
	return mat4::translation(t).eval();
}

TNVX_CODEGEN mf4 cg_mat_scaling_scalar_value(float x, float y, float z)
{
	return mat4::scaling(x, y, z).eval();
}

TNVX_CODEGEN mf4 cg_mat_identity_value()
{
	return mat4::identity().eval();
}
