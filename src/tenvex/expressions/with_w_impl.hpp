#pragma once

#include "with_w.h"

namespace tnvx
{

template<vec_expr L, vec_expr R>
TNVX_INLINE
WithW<L, R>::WithW(const L& TNVX_RESTRICT l, const R& TNVX_RESTRICT r) noexcept
	: _l(l)
	, _r(r)
{
}

template<vec_expr L, vec_expr R>
inline TNVX_INLINE vf4 WithW<L, R>::eval() const noexcept
{
	return detail::with_w(_l.eval(), _r.eval());
}

template<vec_expr L, vec_expr R>
TNVX_INLINE WithW<L, R> with_w(const L& l, const R& r) noexcept
{
	return { l, r };
}

}
