#pragma once

#include "inverse.h"

namespace tnvx
{

template<quat_expr E>
TNVX_INLINE 
Inverse<E>::Inverse(const E& TNVX_RESTRICT e) noexcept
	: _e(e)
{
}

template<quat_expr E>
TNVX_INLINE
Inverse<E>::result_t Inverse<E>::eval() const noexcept
{
	return detail::inverse(_e.eval());
}

template<quat_expr E>
TNVX_INLINE
Inverse<E> inverse(const E & e) noexcept
{
	return Inverse<E>(e);
}

}
