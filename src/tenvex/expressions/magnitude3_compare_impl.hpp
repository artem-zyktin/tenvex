#pragma once

#include "magnitude3_compare.h"

namespace tnvx
{

template<vec_expr A, vec_expr B>
TNVX_INLINE
std::partial_ordering operator<=>(const Magn3<A>& a, const Magn3<B>& b) noexcept
{
	return float(magnitude3_sq(a.operand())) <=> float(magnitude3_sq(b.operand()));
}

template<vec_expr A, class F> requires std::is_arithmetic_v<F>
TNVX_INLINE
std::partial_ordering operator<=>(const Magn3<A>& a, F c) noexcept
{
	const float cc = float(c) * float(c);
	return float(magnitude3_sq(a.operand())) <=> cc;
}

template<vec_expr A, class F> requires std::is_arithmetic_v<F>
TNVX_INLINE
std::partial_ordering operator<=>(F c, const Magn3<A>& a) noexcept
{
	const float cc = float(c) * float(c);
	return cc <=> float(magnitude3_sq(a.operand()));
}

}
