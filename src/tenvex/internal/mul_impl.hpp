#pragma once

#include "mul.h"

namespace tnvx
{

template<expression L, expression R>
TNVX_INLINE
inline Mul<L, R>::Mul(const L& TNVX_RESTRICT l, const R& TNVX_RESTRICT r) noexcept
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

//template<vector_expression L, vector_expression R>
//TNVX_INLINE
//Mul<L, R> operator*(const Expr<L>& l, const Expr<R>& r) noexcept
//{
//	return { l.self(), r.self() };
//}

template<expression E>
TNVX_INLINE
Mul<E, Scalar> operator*(const Expr<E>& l, float r) noexcept
{
	return { l.self(), Scalar(r) };
}

template<expression E>
TNVX_INLINE
Mul<Scalar, E> operator*(float l, const Expr<E>& r) noexcept
{
	return { Scalar(l), r.self() };
}

}
