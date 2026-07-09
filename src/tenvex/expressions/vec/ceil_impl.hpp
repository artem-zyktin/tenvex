#pragma once

#include "ceil.h"

namespace tnvx
{

template<vec_expr E>
TNVX_INLINE
Ceil<E>::Ceil(const E& TNVX_RESTRICT e) noexcept
	: _e(e)
{
}

template<vec_expr E>
TNVX_INLINE
Ceil<E>:: result_t Ceil<E>::eval() const noexcept
{
	return detail::ceil(_e.eval());
}

template<vec_expr E>
TNVX_INLINE
Ceil<E> ceil(const E& e) noexcept
{
	return Ceil<E>(e);
}

}
