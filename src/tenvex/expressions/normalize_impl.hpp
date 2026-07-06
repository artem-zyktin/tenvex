#pragma once

#include "normalize.h"

namespace tnvx
{

template<quat_expr E>
TNVX_INLINE
Normalize<E>::Normalize(const E& TNVX_RESTRICT e) noexcept
	: _e(e)
{
}

template<quat_expr E>
TNVX_INLINE
vf4 Normalize<E>::eval() const noexcept
{
	return detail::normalize(_e.eval());
}

template<quat_expr E>
TNVX_INLINE
Normalize<E> normalize(const E& e) noexcept
{
	return Normalize<E>(e);
}

}
