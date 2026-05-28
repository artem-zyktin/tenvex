#pragma once

#include "expression.h"

namespace tnvx
{

template<vector_expression E>
struct Norm : Expr<Norm<E>>
{
	inline
	Norm(const E& TNVX_RESTRICT e) noexcept;

	[[nodiscard]] inline
	__m128 eval() const noexcept;

private:
	tnvx_type_storage<E> _e;
};

template<vector_expression E>
[[nodiscard]] inline
Norm<E> norm(const Expr<E>& e) noexcept;

}

#include "norm_impl.hpp"
