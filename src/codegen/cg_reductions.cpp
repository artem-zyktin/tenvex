#include "codegen.h"

// Horizontal reductions and the de-sqrt'd magnitude comparisons.
//
// What to look for:
// - dot3 / dot4: the cross-lane sum dominates; dot4 may use hadd (SSE) or
//   vaddvq (NEON).
// - cg_mag3_lt_*: the ordered comparisons must contain NO sqrt instruction -
//   the whole point of the magnitude3_compare rewrite. cg_magnitude3 (the
//   plain length) is the control: it must contain exactly one sqrt.

TNVX_CODEGEN void cg_dot3(const vec4* va, const vec4* vb,
                          float* out, std::size_t n)
{
	for (std::size_t i = 0; i < n; ++i)
		out[i] = dot3(va[i], vb[i]);
}

TNVX_CODEGEN void cg_dot4(const vec4* va, const vec4* vb,
                          float* out, std::size_t n)
{
	for (std::size_t i = 0; i < n; ++i)
		out[i] = dot4(va[i], vb[i]);
}

TNVX_CODEGEN void cg_magnitude3(const vec4* va, float* out, std::size_t n)
{
	for (std::size_t i = 0; i < n; ++i)
		out[i] = magnitude3(va[i]);
}

TNVX_CODEGEN void cg_magnitude3_sq(const vec4* va, float* out, std::size_t n)
{
	for (std::size_t i = 0; i < n; ++i)
		out[i] = magnitude3_sq(va[i]);
}

// |a| < |b| - rewritten to squared lengths, no sqrt on either side
TNVX_CODEGEN void cg_mag3_lt_mag3(const vec4* va, const vec4* vb,
                                  bool* out, std::size_t n)
{
	for (std::size_t i = 0; i < n; ++i)
		out[i] = magnitude3(va[i]) < magnitude3(vb[i]);
}

// |a| < r - one side squared, no sqrt (precondition r >= 0)
TNVX_CODEGEN void cg_mag3_lt_scalar(const vec4* va, float r,
                                    bool* out, std::size_t n)
{
	for (std::size_t i = 0; i < n; ++i)
		out[i] = magnitude3(va[i]) < r;
}
