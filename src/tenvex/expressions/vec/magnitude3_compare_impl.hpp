#pragma once

#include "magnitude3_compare.h"

namespace tnvx
{

template<vec_expr A, vec_expr B>
TNVX_INLINE
bool operator<(const Magn3<A>& a, const Magn3<B>& b) noexcept
{
	return float(magnitude3_sq(a.operand())) < float(magnitude3_sq(b.operand()));
}

template<vec_expr A, typename F>
requires std::is_arithmetic_v<F>
TNVX_INLINE
bool operator<(const Magn3<A>& a, F c) noexcept
{
	if (c < 0)
	{
		return false;
	}

	return float(magnitude3_sq(a.operand())) < float(c) * float(c);
}

template<vec_expr A, typename F>
requires std::is_arithmetic_v<F>
TNVX_INLINE
bool operator<(F c, const Magn3<A>& a) noexcept
{
	if (c < 0)
	{
		return true;
	}

	return float(c) * float(c) < float(magnitude3_sq(a.operand()));
}

template<vec_expr A, vec_expr B>
TNVX_INLINE
bool operator<=(const Magn3<A>& a, const Magn3<B>& b) noexcept
{
	return float(magnitude3_sq(a.operand())) <= float(magnitude3_sq(b.operand()));
}

template<vec_expr A, typename F>
requires std::is_arithmetic_v<F> 
TNVX_INLINE
bool operator<=(const Magn3<A>& a, F c) noexcept
{
	if (c < 0)
	{
		return false;
	}

	return float(magnitude3_sq(a.operand())) <= float(c) * float(c);
}

template<vec_expr A, typename F>
requires std::is_arithmetic_v<F> 
TNVX_INLINE
bool operator<=(F c, const Magn3<A>& a) noexcept
{
	if (c < 0)
	{
		return true;
	}

	return float(c) * float(c) <= float(magnitude3_sq(a.operand()));
}

template<vec_expr A, vec_expr B> 
TNVX_INLINE
bool operator>(const Magn3<A>& a, const Magn3<B>& b) noexcept
{
	return float(magnitude3_sq(a.operand())) > float(magnitude3_sq(b.operand()));
}

template<vec_expr A, typename F>
requires std::is_arithmetic_v<F>
TNVX_INLINE
bool operator>(const Magn3<A>& a, F c) noexcept
{
	if (c < 0)
	{
		return true;
	}

	return float(magnitude3_sq(a.operand())) > float(c) * float(c);
}

template<vec_expr A, typename F>
requires std::is_arithmetic_v<F>
TNVX_INLINE
bool operator>(F c, const Magn3<A>& a) noexcept
{
	if (c < 0)
	{
		return false;
	}

	return float(c) * float(c) > float(magnitude3_sq(a.operand()));
}

template<vec_expr A, vec_expr B>
TNVX_INLINE
bool operator>=(const Magn3<A>& a, const Magn3<B>& b) noexcept
{
	return float(magnitude3_sq(a.operand())) >= float(magnitude3_sq(b.operand()));
}

template<vec_expr A, typename F>
requires std::is_arithmetic_v<F>
TNVX_INLINE
bool operator>=(const Magn3<A>& a, F c) noexcept
{
	if (c < 0)
	{
		return true;
	}

	return float(magnitude3_sq(a.operand())) >= float(c) * float(c);
}

template<vec_expr A, typename F>
requires std::is_arithmetic_v<F>
TNVX_INLINE
bool operator>=(F c, const Magn3<A>& a) noexcept
{
	if (c < 0)
	{
		return false;
	}

	return float(c) * float(c) >= float(magnitude3_sq(a.operand()));
}

}
