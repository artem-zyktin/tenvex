#pragma once

#include "floor.h"

namespace tnvx
{

template<vec_expr E>
TNVX_INLINE 
Floor<E>::Floor(const E& TNVX_RESTRICT e) noexcept
	: _e(e)
{
}

template<vec_expr E>
TNVX_INLINE
vf4 Floor<E>::eval() const noexcept
{
	return detail::floor(_e.eval());
}

template<vec_expr E>
TNVX_INLINE
Floor<E> floor(const E& e) noexcept
{
	return Floor<E>(e);
}

}
