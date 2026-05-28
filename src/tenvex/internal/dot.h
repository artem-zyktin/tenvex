#pragma once

#include "expression.h"
#include "scalar.h"
#include "../vec4.h"

namespace tnvx
{

template<vector_expression L, vector_expression R>
requires (!std::same_as<L, Scalar> && !std::same_as<R, Scalar>)
struct Dot : Expr<Dot>
{
	inline
	Dot(const L& TNVX_RESTRICT l, const R& TNVX_RESTRICT r) noexcept;

	[[nodiscard]] inline
	__m128 eval() const noexcept;

private:
	tnvx_type_storage<L> _l;
	tnvx_type_storage<R> _r;
};

template<vector_expression L, vector_expression R>
[[nodiscard]] inline
Dot<L, R> dot(const Expr<L>& l, const Expr<L>& r) noexcept;

}

#include "dot_impl.hpp"
