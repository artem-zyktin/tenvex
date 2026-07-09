#pragma once

#include "normalize3.h"

namespace tnvx
{

template<packed_expr E>
TNVX_INLINE
Normalize3<E>::Normalize3(const E& TNVX_RESTRICT e) noexcept
	: _e(e)
{
}

template<packed_expr E>
TNVX_INLINE
Normalize3<E>::result_t Normalize3<E>::eval() const noexcept
{
	return detail::normalize3(_e.eval());
}

template<packed_expr E>
TNVX_INLINE
Normalize3<E> normalize3(const E& e) noexcept
{
	return Normalize3<E>(e);
}

}
