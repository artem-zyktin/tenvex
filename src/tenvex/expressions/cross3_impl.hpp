#pragma once

#include "cross3.h"

namespace tnvx
{

template<vec_expr L, vec_expr R>
TNVX_INLINE
Cross3<L, R>::Cross3(const L& TNVX_RESTRICT l, const R& TNVX_RESTRICT r) noexcept
	: _l(l)
	, _r(r)
{
}

template<vec_expr L, vec_expr R>
TNVX_INLINE
vf4 Cross3<L, R>::eval() const noexcept
{
	return detail::cross3(_l.eval(), _r.eval());
}

template<vec_expr L, vec_expr R>
TNVX_INLINE
Cross3<L, R> cross3(const L& l, const R& r) noexcept
{
	return { l, r };
}

}
