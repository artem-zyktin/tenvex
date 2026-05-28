#pragma once

#include "add.h"

namespace tnvx
{

template<expression L, expression R>
Add<L, R>::Add(const L& TNVX_RESTRICT l, const R& TNVX_RESTRICT r) noexcept
	: _l(l)
	, _r(r)
{

}

template<expression L, expression R>
TNVX_INLINE
__m128 Add<L, R>::eval() const noexcept
{
	return _mm_add_ps(_l.eval(), _r.eval());
}

template<expression L, expression R>
TNVX_INLINE
Add<L, R> operator+(const Expr<L>& l, const Expr<R>& r) noexcept
{
	return { l.self(), r.self() };
}

} // namespace tnvx
