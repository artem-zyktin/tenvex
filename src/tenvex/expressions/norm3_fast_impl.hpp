#pragma once

#include "norm3_fast.h"

namespace tnvx
{

template<vec_expr E>
TNVX_INLINE
Norm3Fast<E>::Norm3Fast(const E& TNVX_RESTRICT e) noexcept
	: _e(e)
{
}

template<vec_expr E>
TNVX_INLINE
vf4 Norm3Fast<E>::eval() const noexcept
{
	return detail::norm3_fast(_e.eval());
}

template<vec_expr E>
TNVX_INLINE
Norm3Fast<E> norm3_fast(const E& e) noexcept
{
	return Norm3Fast<E>(e);
}

}