#pragma once

#include "conjugate.h"

namespace tnvx
{

template<quat_expr E>
TNVX_INLINE
Conj<E>::Conj(const E& TNVX_RESTRICT expr) noexcept
	: _e(expr)
{
}

template<quat_expr E>
TNVX_INLINE
vf4 Conj<E>::eval() const noexcept
{
	return detail::conjugate(_e.eval());
}

template<quat_expr E>
TNVX_INLINE
Conj<E> conj(const E& q) noexcept
{
	return Conj<E>(q);
}

}
