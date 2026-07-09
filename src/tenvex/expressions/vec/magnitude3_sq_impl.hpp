#pragma once

#include "magnitude3_sq.h"

namespace tnvx
{

template<vec_expr E>
TNVX_INLINE 
Magn3Sq<E>::Magn3Sq(const E& TNVX_RESTRICT e) noexcept
	: _e(e)
{
}

template<vec_expr E>
TNVX_INLINE
Magn3Sq<E>::result_t Magn3Sq<E>::eval() const noexcept
{
	return detail::magnitude3_sq(_e.eval());
}

template<vec_expr E>
TNVX_INLINE
Magn3Sq<E>::operator float() const noexcept
{
	return detail::to_float(eval());
}

template<vec_expr E>
TNVX_INLINE
Magn3Sq<E> magnitude3_sq(const E& e) noexcept
{
	return Magn3Sq<E>(e);
}


}
