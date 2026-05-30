#pragma once

#include "norm3.h"

namespace tnvx
{

template<vec_expr E>
TNVX_INLINE
Norm3<E>::Norm3(const E& TNVX_RESTRICT e) noexcept
	: _e(e)
{
}

template<vec_expr E>
TNVX_INLINE
vf4 Norm3<E>::eval() const noexcept
{
	return detail::norm3(_e.eval());
}

template<vec_expr E>
TNVX_INLINE
Norm3<E> norm3(const E& TNVX_RESTRICT e) noexcept
{
	return Norm3<E>(e);
}

}
