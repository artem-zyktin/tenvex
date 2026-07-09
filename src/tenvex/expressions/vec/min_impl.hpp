#pragma once

#include "min.h"

namespace tnvx
{

template<vec_expr L, vec_expr R>
TNVX_INLINE
Min<L, R>::Min(const L& TNVX_RESTRICT l, const R& TNVX_RESTRICT r) noexcept
	: _l(l)
	, _r(r)
{
}

template<vec_expr L, vec_expr R>
TNVX_INLINE
Min<L, R>::result_t Min<L, R>::eval() const noexcept
{
	return detail::min(_l.eval(), _r.eval());
}

template<vec_expr L, vec_expr R>
TNVX_INLINE
Min<L, R> min(const L& l, const R& r) noexcept
{
	return { l, r };
}

}
