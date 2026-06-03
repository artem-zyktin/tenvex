#pragma once

#include "dot4.h"

namespace tnvx
{

template<vec_expr L, vec_expr R>
TNVX_INLINE
Dot4<L, R>::Dot4(const L& TNVX_RESTRICT l, const R& TNVX_RESTRICT r) noexcept
	: _l(l)
	, _r(r)
{
}

template<vec_expr L, vec_expr R>
TNVX_INLINE
vf4 Dot4<L, R>::eval() const noexcept
{
	return detail::dot4(_l.eval(), _r.eval());
}

template<vec_expr L, vec_expr R>
TNVX_INLINE
Dot4<L, R>::operator float() const noexcept
{
	return detail::to_float(eval());
}

template<vec_expr L, vec_expr R>
TNVX_INLINE
Dot4<L, R> dot4(const L& l, const R& r) noexcept
{
	return { l, r };
}

}
