#pragma once

#include "magnitude3.h"
#include "dot3.h"

namespace tnvx
{

template<vec_expr E>
TNVX_INLINE
Magn3<E>::Magn3(const E& TNVX_RESTRICT e) noexcept
	: _e(e)
{
}

template<vec_expr E>
TNVX_INLINE
vf4 Magn3<E>::eval() const noexcept
{
	return detail::magnitude3(_e.eval());
}

template<vec_expr E>
TNVX_INLINE
Magn3<E>::operator float() const noexcept
{
	return _mm_cvtss_f32(eval());
}

template<vec_expr E>
TNVX_INLINE
Magn3<E> magnitude3(const E& e) noexcept
{
	return Magn3<E>(e);
}

}
