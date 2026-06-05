#pragma once

#include "max.h"

namespace tnvx
{

template<vec_expr L, vec_expr R>
TNVX_INLINE 
Max<L, R>::Max(const L& TNVX_RESTRICT l, const R& TNVX_RESTRICT r) noexcept
	: _l(l)
	, _r(r)
{
}

template<vec_expr L, vec_expr R>
TNVX_INLINE
vf4 Max<L, R>::eval() const noexcept
{
	return detail::max(_l.eval(), _r.eval());
}


template<vec_expr L, vec_expr R>
TNVX_INLINE
Max<L, R> max(const L& l, const R& r) noexcept
{
	return { l, r };
}

}
