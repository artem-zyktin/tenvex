#pragma once

#include "determinant.h"

namespace tnvx
{

template<mat_expr E>
TNVX_INLINE
Determinant<E>::Determinant(const E& TNVX_RESTRICT e) noexcept
	: _e(e)
{
}

template<mat_expr E>
TNVX_INLINE
Determinant<E>::result_t Determinant<E>::eval() const noexcept
{
	return detail::mat_determinant(_e.eval());
}

template<mat_expr E>
TNVX_INLINE
Determinant<E>::operator float() const noexcept
{
	return detail::to_float(eval());
}

template<mat_expr E>
TNVX_INLINE
Determinant<E> determinant(const E& m) noexcept
{
	return Determinant<E>(m);
}

}
