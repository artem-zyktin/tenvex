#include "codegen.h"

// Reference pair: a worked example of what a spill looks like in a listing.
// Not a probe of the library - a calibration sample for the reader.
//
// cg_clean: the kernel inlines, everything stays in registers -> the body
// is pure arithmetic, no stack traffic.
// cg_spilled: the kernel is opaque (no definition in this TU), the value of
// `c` must survive a call -> the compiler has no choice but to spill it.
// Expected: a stack frame, a store before the first call, a load after.

extern "C" vf4 cg_opaque_kernel(vf4 x, vf4 y);   // deliberately undefined

static TNVX_INLINE vf4 fused_kernel(vf4 x, vf4 y)
{
	return detail::add(detail::mul(x, y), y);
}

TNVX_CODEGEN vf4 cg_clean(vf4 a, vf4 b, vf4 c)
{
	return fused_kernel(fused_kernel(a, b), c);
}

TNVX_CODEGEN vf4 cg_spilled(vf4 a, vf4 b, vf4 c)
{
	return cg_opaque_kernel(cg_opaque_kernel(a, b), c);
}
