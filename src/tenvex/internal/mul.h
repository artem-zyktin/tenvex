#pragma once

#include "expression.h"
#include "scalar.h"

namespace tnvx
{

template<expression L, expression R>
struct Mul : Expr<Mul<L, R>>
{
	inline
	Mul(const L& TNVX_RESTRICT l, const R& TNVX_RESTRICT r) noexcept;

	[[nodiscard]] inline
	__m128 eval() const noexcept;

private:
	tnvx_type_storage<L> _l;
	tnvx_type_storage<R> _r;
};

template<expression E>
[[nodiscard]] inline
Mul<E, Scalar> operator*(const Expr<E>& l, float r) noexcept;

template<expression E>
[[nodiscard]] inline
Mul<Scalar, E> operator*(float l, const Expr<E>& r) noexcept;

}

#include "mul_impl.hpp"
