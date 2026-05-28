#pragma once

#include "sub.h"

namespace tnvx
{

template<expression L, expression R>
tnvx::Sub<L, R>::Sub(const L& TNVX_RESTRICT l, const R& TNVX_RESTRICT r) noexcept
	: _l(l), _r(r)
{
}

template<expression L, expression R>
TNVX_INLINE
__m128 Sub<L, R>::eval() const noexcept
{
	return _mm_sub_ps(_l.eval(), _r.eval());
}

template<expression L, expression R>
TNVX_INLINE
Sub<L, R> operator-(const Expr<L>& l, const Expr<R>& r) noexcept
{
	return { l.self(), r.self() };
}

}
