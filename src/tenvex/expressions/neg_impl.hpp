#pragma once

#include "neg.h"

namespace tnvx
{

template<expression E>
TNVX_INLINE
tnvx::Neg<E>::Neg(const E& TNVX_RESTRICT e) noexcept
	: _e(e)
{
}

template<expression E>
TNVX_INLINE
Neg<E>::result_t Neg<E>::eval() const noexcept
{
	return detail::neg(_e.eval());
}

template<expression E>
TNVX_INLINE
Neg<E>::operator float() const noexcept requires scalar_expr<E>
{
	return detail::to_float(eval());
}

template<expression E>
TNVX_INLINE
Neg<E> operator-(const E& e) noexcept
{
	return Neg<E>(e);
}

}
