#pragma once

#include "div.h"

namespace tnvx
{

template<vec_expr L, scalar_expr R>
TNVX_INLINE
tnvx::Div<L, R>::Div(const L& TNVX_RESTRICT l, const R& TNVX_RESTRICT r) noexcept
	: _l(l)
	, _r(r)
{
}

template<vec_expr L, scalar_expr R>
TNVX_INLINE
vf4 Div<L, R>::eval() const noexcept
{
	return detail::div(_l.eval(), _r.eval());
}

template<vec_expr E>
TNVX_INLINE
Div<E, Scalar> operator/(const E& l, float r) noexcept
{
	return { l, Scalar(r) };
}

template<vec_expr L, scalar_expr R>
TNVX_INLINE Div<L, R> operator/(const L& l, const R& r) noexcept
{
	return { l, r };
}

}
