#pragma once

#include "inverse.h"

namespace tnvx
{

template<mat_expr E>
TNVX_INLINE
MatInverse<E>::MatInverse(const E& TNVX_RESTRICT e) noexcept
	: _e(e)
{
}

template<mat_expr E>
TNVX_INLINE
MatInverse<E>::result_t MatInverse<E>::eval() const noexcept
{
	return detail::mat_inverse(_e.eval());
}

template<mat_expr E>
TNVX_INLINE
MatInverse<E> inverse(const E& m) noexcept
{
	return MatInverse<E>(m);
}

}
