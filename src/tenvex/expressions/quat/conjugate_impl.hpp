#pragma once

#include "conjugate.h"

namespace tnvx
{

template<quat_expr E>
TNVX_INLINE
Conjugate<E>::Conjugate(const E& TNVX_RESTRICT expr) noexcept
	: _e(expr)
{
}

template<quat_expr E>
TNVX_INLINE
Conjugate<E>::result_t Conjugate<E>::eval() const noexcept
{
	return detail::conjugate(_e.eval());
}

template<quat_expr E>
TNVX_INLINE
Conjugate<E> conjugate(const E& q) noexcept
{
	return Conjugate<E>(q);
}

}
