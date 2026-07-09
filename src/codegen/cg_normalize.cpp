#include "codegen.h"

// The normalize family.
//
// What to look for:
// - cg_normalize3: exact path - one sqrt + one div + blend (w preserved).
// - cg_normalize3_fast: rsqrt estimate + one Newton-Raphson step, NO sqrt
//   and NO div; on NEON note the length of the dependency chain (this is
//   why it loses on latency there - see README).
// - cg_normalize4: dot4-based, no blend (all four lanes scaled).

TNVX_CODEGEN void cg_normalize3(const vec4* va, vf4* out, std::size_t n)
{
	for (std::size_t i = 0; i < n; ++i)
		out[i] = normalize3(va[i]).eval();
}

TNVX_CODEGEN void cg_normalize3_fast(const vec4* va, vf4* out, std::size_t n)
{
	for (std::size_t i = 0; i < n; ++i)
		out[i] = normalize3_fast(va[i]).eval();
}

TNVX_CODEGEN void cg_normalize4(const quat* qa, vf4* out, std::size_t n)
{
	for (std::size_t i = 0; i < n; ++i)
		out[i] = normalize4(qa[i]).eval();
}
