#include "codegen.h"

// Element-wise nodes in realistic shapes.
//
// What to look for:
// - cg_aabb: min/max fold into two register accumulators; the loop body
//   should be two loads + min + max, no stack traffic, bounds written once
//   after the loop.
// - cg_saturate: representative single-op pass (min+max against constants
//   hoisted out of the loop) - the shape README calls memory-bandwidth
//   bound.
// - cg_with_w_expr: the blend fuses into the expression - no extra moves
//   for the w lane.

TNVX_CODEGEN void cg_aabb(const vec4* pts, std::size_t n,
                          vf4* lo_out, vf4* hi_out)
{
	vec4 lo = pts[0], hi = pts[0];
	for (std::size_t i = 1; i < n; ++i)
	{
		lo = min(lo, pts[i]);
		hi = max(hi, pts[i]);
	}
	*lo_out = lo.eval();
	*hi_out = hi.eval();
}

TNVX_CODEGEN void cg_saturate(const vec4* va, vf4* out, std::size_t n)
{
	for (std::size_t i = 0; i < n; ++i)
		out[i] = saturate(va[i]).eval();
}

TNVX_CODEGEN void cg_with_w_expr(const vec4* va, const vec4* vb,
                                 vf4* out, std::size_t n)
{
	for (std::size_t i = 0; i < n; ++i)
		out[i] = with_w(va[i] + vb[i], va[i]).eval();
}
