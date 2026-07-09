#pragma once

#include "sub.h"

namespace tnvx
{

template<expression L, expression R>
requires same_category<L, R>
TNVX_INLINE
Sub<L, R>::Sub(const L& TNVX_RESTRICT l, const R& TNVX_RESTRICT r) noexcept
	: _l(l)
	, _r(r)
{
}

template<expression L, expression R>
requires same_category<L, R>
TNVX_INLINE
Sub<L, R>::result_t Sub<L, R>::eval() const noexcept
{
	return detail::sub(_l.eval(), _r.eval());
}

template<expression L, expression R>
requires same_category<L, R>
TNVX_INLINE 
Sub<L, R>::operator float() const noexcept
requires scalar_expr<L> && scalar_expr<R>
{
	return detail::to_float(eval());
}

template<vec_expr L, vec_expr R>
TNVX_INLINE
Sub<L, R> operator-(const L& l, const R& r) noexcept
{
	return { l, r };
}

template<scalar_expr L, scalar_expr R>
TNVX_INLINE
Sub<L, R> operator-(const L& l, const R& r) noexcept
{
	return { l, r };
}

template<scalar_expr E>
TNVX_INLINE
Sub<E, Scalar> operator-(const E& l, float r) noexcept
{
	return { l, Scalar(r) };
}

template<scalar_expr E>
TNVX_INLINE
Sub<Scalar, E> operator-(float l, const E& e) noexcept
{
	return { Scalar(l), e };
}

template<quat_expr L, quat_expr R>
TNVX_INLINE
Sub<L, R> operator-(const L& l, const R& r) noexcept
{
	return { l, r };
}

}
