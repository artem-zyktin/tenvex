#pragma once

#include "magnitude4_sq.h"

namespace tnvx
{

template<packed_expr E>
TNVX_INLINE
Magn4Sq<E>::Magn4Sq(const E& TNVX_RESTRICT e) noexcept
	: _e(e)
{
}

template<packed_expr E>
TNVX_INLINE vf4 Magn4Sq<E>::eval() const noexcept
{
	return detail::magnitude4_sq(_e.eval());
}

template<packed_expr E>
TNVX_INLINE
Magn4Sq<E>::operator float() const noexcept
{
	return detail::to_float(eval());
}

template<packed_expr E>
TNVX_INLINE
Magn4Sq<E> magnitude4_sq(const E& e) noexcept
{
	return Magn4Sq<E>(e);
}

}
