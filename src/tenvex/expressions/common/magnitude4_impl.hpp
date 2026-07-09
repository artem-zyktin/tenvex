#pragma once

#include "magnitude4.h"

namespace tnvx
{

template<packed_expr E>
TNVX_INLINE
Magn4<E>::Magn4(const E& TNVX_RESTRICT e) noexcept
	: _e(e)
{
}

template<packed_expr E>
TNVX_INLINE
Magn4<E>::result_t Magn4<E>::eval() const noexcept
{
	return detail::magnitude4(_e.eval());
}

template<packed_expr E>
TNVX_INLINE
Magn4<E>::operator float() const noexcept
{
	return detail::to_float(eval());
}

template<packed_expr E>
TNVX_INLINE
Magn4<E> magnitude4(const E& e) noexcept
{
	return Magn4<E>(e);
}

}
