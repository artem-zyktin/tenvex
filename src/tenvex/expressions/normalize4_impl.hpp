#pragma once

#include "normalize4.h"

namespace tnvx
{

template<packed_expr E>
TNVX_INLINE
Normalize4<E>::Normalize4(const E& TNVX_RESTRICT e) noexcept
	: _e(e)
{
}

template<packed_expr E>
TNVX_INLINE
vf4 Normalize4<E>::eval() const noexcept
{
	return detail::normalize4(_e.eval());
}

template<packed_expr E>
TNVX_INLINE
Normalize4<E> normalize4(const E& e) noexcept
{
	return Normalize4<E>(e);
}

}
