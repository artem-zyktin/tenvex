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
__m128 Sub<L, R>::eval() const noexcept
{
	return _mm_sub_ps(_l.eval(), _r.eval());
}

template<vec_expr L, vec_expr R>
TNVX_INLINE
Sub<L, R> operator-(const L& l, const R& r) noexcept
{
	return { l, r };
}

}
