#pragma once

#include "magnitude.h"
#include "dot.h"

namespace tnvx
{

template<vector_expression E>
TNVX_INLINE
Magnitude<E>::Magnitude(const E& TNVX_RESTRICT e) noexcept
	: _e(e)
{
}

template<vector_expression E>
TNVX_INLINE
__m128 Magnitude<E>::eval() const noexcept
{
	return _mm_sqrt_ps(Dot<E, E>(_e, _e).eval());
}

template<vector_expression E>
TNVX_INLINE
Magnitude<E> magnitude(const Expr<E> e) noexcept
{
	return { e.self() };
}

}
