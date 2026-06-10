#pragma once

#include "frac.h"

namespace tnvx
{

template<vec_expr E>
TNVX_INLINE
Frac<E>::Frac(const E& TNVX_RESTRICT e) noexcept
	: _e(e)
{
}

template<vec_expr E>
TNVX_INLINE
vf4 Frac<E>::eval() const noexcept
{
	return detail::frac(_e.eval());
}

template<vec_expr E>
TNVX_INLINE
Frac<E> frac(const E& e) noexcept
{
	return Frac<E>(e);
}

}
