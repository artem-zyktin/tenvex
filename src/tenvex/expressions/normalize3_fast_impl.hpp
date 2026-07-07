#pragma once

#include "normalize3_fast.h"

namespace tnvx
{

template<packed_expr E>
TNVX_INLINE
Normalize3Fast<E>::Normalize3Fast(const E& TNVX_RESTRICT e) noexcept
	: _e(e)
{
}

template<packed_expr E>
TNVX_INLINE
vf4 Normalize3Fast<E>::eval() const noexcept
{
	return detail::normalize3_fast(_e.eval());
}

template<packed_expr E>
TNVX_INLINE
Normalize3Fast<E> normalize3_fast(const E& e) noexcept
{
	return Normalize3Fast<E>(e);
}

}