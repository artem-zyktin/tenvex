#pragma once

#include "dot3.h"

namespace tnvx
{

template<vec_expr L, vec_expr R>
TNVX_INLINE
Dot3<L, R>::Dot3(const L& TNVX_RESTRICT l, const R& TNVX_RESTRICT r) noexcept
	: _l(l)
	, _r(r)
{
}

template<vec_expr L, vec_expr R>
TNVX_INLINE
Dot3<L, R>::result_t Dot3<L, R>::eval() const noexcept
{
	return detail::dot3(_l.eval(), _r.eval());
}

template<vec_expr L, vec_expr R>
TNVX_INLINE
Dot3<L, R>::operator float() const noexcept
{
	return detail::to_float(eval());
}

template<vec_expr L, vec_expr R>
TNVX_INLINE
Dot3<L, R> dot3(const L& l, const R& r) noexcept
{
	return { l, r };
}

}
