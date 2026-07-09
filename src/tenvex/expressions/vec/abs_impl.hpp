#pragma once

#include "abs.h"

namespace tnvx
{

template<vec_expr E>
TNVX_INLINE
Abs<E>::Abs(const E& TNVX_RESTRICT e) noexcept
	: _e(e)
{
}

template<vec_expr E>
TNVX_INLINE Abs<E>::result_t Abs<E>::eval() const noexcept
{
	return detail::abs(_e.eval());
}

template<vec_expr E>
TNVX_INLINE Abs<E> abs(const E& e) noexcept
{
	return Abs<E>(e);
}

}
