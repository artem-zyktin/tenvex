#pragma once

#include "expression.h"

namespace tnvx
{

template<vector_expression L, vector_expression R>
struct Dot : Expr<Dot<L, R>>
{
	inline
	Dot(const L& TNVX_RESTRICT l, const R& TNVX_RESTRICT r) noexcept;

	[[nodiscard]] inline
	__m128 eval() const noexcept;

	[[nodiscard]] inline
	operator float() const noexcept;

private:
	tnvx_type_storage<L> _l;
	tnvx_type_storage<R> _r;
};

template<vector_expression L, vector_expression R>
[[nodiscard]] inline
Dot<L, R> dot(const Expr<L>& l, const Expr<R>& r) noexcept;

template<vector_expression L, vector_expression R>
[[nodiscard]] inline
float operator*(const Dot<L, R>& l, float r) noexcept;

template<vector_expression L, vector_expression R>
[[nodiscard]] inline
float operator*(float l, const Dot<L, R>& r) noexcept;

}

#include "dot_impl.hpp"
