#pragma once

#include "expression.h"

namespace tnvx
{

template<typename Derived>
TNVX_INLINE
const Derived& Expr<Derived>::self() const noexcept
{
	return static_cast<const Derived&>(*this);
}

template<typename Derived>
TNVX_INLINE
__m128 Expr<Derived>::eval() const noexcept
{
	return self().eval();
}

template<typename Derived>
TNVX_INLINE
float Expr<Derived>::operator[](size_t i) const noexcept
{
	alignas(16) float tmp[4];
	_mm_store_ps(tmp, eval());
	return tmp[i];
}

} // namespace tnvx