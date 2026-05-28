#pragma once

#include "norm.h"
#include "dot.h"

namespace tnvx
{

template<vector_expression E>
TNVX_INLINE
Norm<E>::Norm(const E& TNVX_RESTRICT e) noexcept
	: _e(e)
{
}

template<vector_expression E>
TNVX_INLINE
__m128 Norm<E>::eval() const noexcept
{
	__m128 data = _e.eval();
	__m128 mul = _mm_mul_ps(data, data);
	__m128 shuf = _mm_shuffle_ps(mul, mul, _MM_SHUFFLE(2, 3, 0, 1));
	__m128 sum = _mm_add_ps(mul, shuf);
	shuf = _mm_movehl_ps(shuf, sum);
	sum = _mm_add_ss(sum, shuf);
	__m128 len = _mm_shuffle_ps(sum, sum, 0);
	return _mm_div_ps(data, len);
}

template<vector_expression E>
Norm<E> norm(const Expr<E> e) noexcept
{
	return { e.self() };
}

}
