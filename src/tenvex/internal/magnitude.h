#pragma once

#include "expression.h"

namespace tnvx
{

template<vector_expression E>
struct Magnitude : Expr<Magnitude<E>>
{
	inline
	Magnitude(const E& TNVX_RESTRICT e) noexcept;

	[[nodiscard]] inline
	__m128 eval() const noexcept;

	[[nodiscard]] inline
	operator float() const noexcept;

private:
	tnvx_type_storage<E> _e;
};

template<vector_expression E>
[[nodiscard]] inline
Magnitude<E> magnitude(const Expr<E>& e) noexcept;

}

#include "magnitude_impl.hpp"
