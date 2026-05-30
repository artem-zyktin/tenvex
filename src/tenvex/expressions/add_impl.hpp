#pragma once

#include "add.h"

namespace tnvx
{

template<vec_expr L, vec_expr R>
TNVX_INLINE
Add<L, R>::Add(const L& TNVX_RESTRICT l, const R& TNVX_RESTRICT r) noexcept
	: _l(l)
	, _r(r)
{
}

template<vec_expr L, vec_expr R>
[[nodiscard]] TNVX_INLINE
vf4 Add<L, R>::eval() const noexcept
{
	return detail::add(_l.eval(), _r.eval());
}

template<vec_expr L, vec_expr R>
[[nodiscard]] TNVX_INLINE
Add<L, R> operator+(const L& TNVX_RESTRICT l, const R& TNVX_RESTRICT r) noexcept
{
	return { l, r };
}

}
