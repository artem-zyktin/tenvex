#pragma once

#include "dot.h"

namespace tnvx
{

template<vector_expression L, vector_expression R>
TNVX_INLINE
Dot<L, R>::Dot(const L& TNVX_RESTRICT l, const R& TNVX_RESTRICT r) noexcept
	: _l(l)
	, _r(r)
{
}

template<vector_expression L, vector_expression R>
TNVX_INLINE
__m128 Dot<L, R>::eval() const noexcept
{
	__m128 a = _l.eval();
	__m128 b = _r.eval();

	__m128 mul = _mm_mul_ps(a, b);
	__m128 shuf = _mm_shuffle_ps(mul, mul, _MM_SHUFFLE(2, 3, 0, 1));
	__m128 sum = _mm_add_ps(mul, shuf);
	shuf = _mm_movehl_ps(shuf, sum);
	sum = _mm_add_ss(sum, shuf);
	return _mm_shuffle_ps(sum, sum, 0);
}

template<vector_expression L, vector_expression R>
TNVX_INLINE
Dot<L, R>::operator float() const noexcept
{
	return _mm_cvtss_f32(eval());
}

template<vector_expression L, vector_expression R>
TNVX_INLINE
Dot<L, R> dot(const Expr<L>& l, const Expr<R>& r) noexcept
{
	return { l.self(), r.self() };
}

template<vector_expression L, vector_expression R>
TNVX_INLINE
float operator*(const Dot<L, R>& l, float r) noexcept
{
	return static_cast<float>(l) * r;
}

template<vector_expression L, vector_expression R>
float operator*(float l, const Dot<L, R>& r) noexcept
{
	return l * static_cast<float>(r);
}



}
