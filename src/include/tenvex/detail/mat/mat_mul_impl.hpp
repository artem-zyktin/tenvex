#pragma once

#include "mat_mul.h"

namespace tnvx
{

template<mat_expr L, mat_expr R>
TNVX_INLINE
MatMul<L, R>::MatMul(const L& TNVX_RESTRICT l, const R& TNVX_RESTRICT r) noexcept
	: _l(l)
	, _r(r)
{
}

template<mat_expr L, mat_expr R>
TNVX_INLINE
MatMul<L, R>::result_t MatMul<L, R>::eval() const noexcept
{
	return detail::mat_mul(_l.eval(), _r.eval());
}

template<mat_expr L, mat_expr R>
TNVX_INLINE
MatMul<L, R> operator*(const L& l, const R& r) noexcept
{
	return { l, r };
}

}
