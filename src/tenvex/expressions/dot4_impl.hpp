#pragma once

#include "dot4.h"

namespace tnvx
{

template<packed_expr L, packed_expr R>
requires same_packed_category<L, R>
TNVX_INLINE
Dot4<L, R>::Dot4(const L& TNVX_RESTRICT l, const R& TNVX_RESTRICT r) noexcept
	: _l(l)
	, _r(r)
{
}

template<packed_expr L, packed_expr R>
requires same_packed_category<L, R>
TNVX_INLINE
Dot4<L, R>::result_t Dot4<L, R>::eval() const noexcept
{
	return detail::dot4(_l.eval(), _r.eval());
}

template<packed_expr L, packed_expr R>
requires same_packed_category<L, R>
TNVX_INLINE
Dot4<L, R>::operator float() const noexcept
{
	return detail::to_float(eval());
}

template<packed_expr L, packed_expr R>
requires same_packed_category<L, R>
TNVX_INLINE
Dot4<L, R> dot4(const L& l, const R& r) noexcept
{
	return { l, r };
}

}
