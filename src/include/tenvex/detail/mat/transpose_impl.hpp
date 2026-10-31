#pragma once

#include "transpose.h"

namespace tnvx
{

template<mat_expr E>
TNVX_INLINE
Transpose<E>::Transpose(const E& TNVX_RESTRICT e) noexcept
	: _e(e)
{
}

template<mat_expr E>
TNVX_INLINE
Transpose<E>::result_t Transpose<E>::eval() const noexcept
{
	return detail::mat_transpose(_e.eval());
}

template<mat_expr E>
TNVX_INLINE
Transpose<E> transpose(const E& m) noexcept
{
	return Transpose<E>(m);
}

}
