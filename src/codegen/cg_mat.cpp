#include "codegen.h"

// Matrix factories and the matrix expression nodes.
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
// - cg_mat_transform: the linear combination the column-major layout is
//   chosen for - 4 broadcasts + 4 multiply-adds (fmla by lane on NEON),
//   no shuffle of the matrix and no horizontal reduction.
// - cg_mat_mul: four of those, one per column of the right operand. The
//   left operand's four registers must stay live across all four.
// - cg_mat_transpose: the shuffle network only (unpck / movlh on SSE,
//   trn / combine on NEON), no arithmetic.
// - cg_mat_determinant: two cross products, two column combinations and
//   two dot3 reductions, collapsing to one broadcast register.
// - cg_mat_inverse: the same decomposition plus the adjugate and a final
//   transpose; one division, the rest multiplies. The widest probe here -
//   this is where to look for spills.
// - cg_mat_transform_fused: transform is a vec_expr, so it must fuse into
//   the surrounding vector expression with no boundary.
// - cg_mat_compose: T * R * S applied to a point, the shape a renderer
//   writes. The intermediate matrices must never reach memory.
// mat4 leaves are held by const& (sizeof is 64), so the node loops are
//   also where that choice is read off the listing: a node carrying a
//   pointer must still be scalarized away.

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

TNVX_CODEGEN void cg_mat_transform(const mat4* ma, const vec4* va,
                                   vf4* out, std::size_t n)
{
	for (std::size_t i = 0; i < n; ++i)
		out[i] = (ma[i] * va[i]).eval();
}

TNVX_CODEGEN void cg_mat_mul(const mat4* ma, const mat4* mb,
                             mf4* out, std::size_t n)
{
	for (std::size_t i = 0; i < n; ++i)
		out[i] = (ma[i] * mb[i]).eval();
}

TNVX_CODEGEN void cg_mat_transpose(const mat4* ma, mf4* out, std::size_t n)
{
	for (std::size_t i = 0; i < n; ++i)
		out[i] = transpose(ma[i]).eval();
}

TNVX_CODEGEN void cg_mat_determinant(const mat4* ma, vf4* out, std::size_t n)
{
	for (std::size_t i = 0; i < n; ++i)
		out[i] = determinant(ma[i]).eval();
}

TNVX_CODEGEN void cg_mat_inverse(const mat4* ma, mf4* out, std::size_t n)
{
	for (std::size_t i = 0; i < n; ++i)
		out[i] = inverse(ma[i]).eval();
}

TNVX_CODEGEN void cg_mat_scale_add(const mat4* ma, const mat4* mb,
                                   mf4* out, std::size_t n)
{
	for (std::size_t i = 0; i < n; ++i)
		out[i] = (ma[i] * 2.0f + mb[i]).eval();
}

TNVX_CODEGEN void cg_mat_transform_fused(const mat4* ma, const vec4* va, const vec4* vb,
                                         vf4* out, std::size_t n)
{
	for (std::size_t i = 0; i < n; ++i)
		out[i] = (ma[i] * va[i] + vb[i] * 2.0f).eval();
}

TNVX_CODEGEN void cg_mat_compose(const vec4* va, const quat* qa,
                                 vf4* out, std::size_t n)
{
	for (std::size_t i = 0; i < n; ++i)
	{
		const mat4 t = mat4::translation(va[i]);
		const mat4 r = mat4::from_quat(qa[i]);
		const mat4 s = mat4::scaling(2.0f);
		out[i] = (t * mat4(r * s) * va[i]).eval();
	}
}

TNVX_CODEGEN vf4 cg_mat_transform_value(const mat4& m, const vec4& v)
{
	return (m * v).eval();
}

TNVX_CODEGEN mf4 cg_mat_mul_value(const mat4& a, const mat4& b)
{
	return (a * b).eval();
}

TNVX_CODEGEN mf4 cg_mat_transpose_value(const mat4& m)
{
	return transpose(m).eval();
}

TNVX_CODEGEN vf4 cg_mat_determinant_value(const mat4& m)
{
	return determinant(m).eval();
}

TNVX_CODEGEN mf4 cg_mat_inverse_value(const mat4& m)
{
	return inverse(m).eval();
}
