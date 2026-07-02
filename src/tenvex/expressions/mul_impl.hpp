#pragma once

#include "mul.h"

namespace tnvx
{

template<expression L, expression R>
requires scalable<L, R>
TNVX_INLINE
Mul<L, R>::Mul(const L& TNVX_RESTRICT l, const R& TNVX_RESTRICT r) noexcept
	: _l(l)
	, _r(r)
{
}

template<expression L, expression R>
requires scalable<L, R>
TNVX_INLINE
vf4 Mul<L, R>::eval() const noexcept
{
	return detail::mul(_l.eval(), _r.eval());
}

template<vec_expr E>
TNVX_INLINE
Mul<E, Scalar> operator*(const E& l, float r) noexcept
{
	return { l, Scalar(r) };
}

template<vec_expr E>
TNVX_INLINE
Mul<Scalar, E> operator*(float l, const E& r) noexcept
{
	return { Scalar(l), r };
}

template<scalar_expr L, scalar_expr R>
TNVX_INLINE
Mul<L, R> operator*(const L& l, const R& r) noexcept
{
	return { l, r };
}

template<scalar_expr L, vec_expr R>
TNVX_INLINE
Mul<L, R> operator*(const L& l, const R& r) noexcept
{
	return { l, r };
}

template<vec_expr L, scalar_expr R>
TNVX_INLINE
Mul<L, R> operator*(const L& l, const R& r) noexcept
{
	return { l, r };
}

template<scalar_expr E>
TNVX_INLINE
Mul<E, Scalar> operator*(const E& l, float r) noexcept
{
	return { l, Scalar(r) };
}

template<scalar_expr E>
TNVX_INLINE
Mul<Scalar, E> operator*(float l, const E& r) noexcept
{
	return { Scalar(l), r };
}

template<quat_expr E>
Mul<Scalar, E> operator*(float l, const E& r) noexcept
{
	return { Scalar(l), r };
}

template<quat_expr E>
Mul<E, Scalar> operator*(const E& l, float r) noexcept
{
	return { l, Scalar(r) };
}

template<quat_expr L, scalar_expr R>
TNVX_INLINE
Mul<L, R> operator*(const L& l, const R& r) noexcept
{
	return { l, r };
}

template<scalar_expr L, quat_expr R>
TNVX_INLINE
Mul<L, R> operator*(const L& l, const R& r) noexcept
{
	return { l, r };
}

}
