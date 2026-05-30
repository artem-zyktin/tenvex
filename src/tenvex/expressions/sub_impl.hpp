#pragma once

#include "sub.h"

namespace tnvx
{

template<vec_expr L, vec_expr R>
TNVX_INLINE
Sub<L, R>::Sub(const L& TNVX_RESTRICT l, const R& TNVX_RESTRICT r) noexcept
	: _l(l)
	, _r(r)
{
}

template<vec_expr L, vec_expr R>
TNVX_INLINE
vf4 Sub<L, R>::eval() const noexcept
{
	return detail::sub(_l.eval(), _r.eval());
}

template<vec_expr L, vec_expr R>
TNVX_INLINE
Sub<L, R> operator-(const L& TNVX_RESTRICT l, const R& TNVX_RESTRICT r) noexcept
{
	return { l, r };
}

}
