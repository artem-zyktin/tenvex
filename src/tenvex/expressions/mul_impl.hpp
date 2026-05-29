#pragma once

#include "mul.h"

namespace tnvx
{

template<expression L, expression R>
TNVX_INLINE
Mul<L, R>::Mul(const L& l, const R& r) noexcept
	: _l(l)
	, _r(r)
{
}

template<expression L, expression R>
TNVX_INLINE
__m128 Mul<L, R>::eval() const noexcept
{
	return _mm_mul_ps(_l.eval(), _r.eval());
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

}
