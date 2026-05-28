#pragma once

#include "expression.h"

namespace tnvx
{

template<vector_expression L, vector_expression R>
struct Cross : Expr<Cross<L, R>>
{
	inline
	Cross(const L& TNVX_RESTRICT l, const R& TNVX_RESTRICT r) noexcept;

	[[nodiscard]] inline
	__m128 eval() const noexcept;

private:
	tnvx_type_storage<L> _l;
	tnvx_type_storage<R> _r;
};

template<vector_expression L, vector_expression R>
[[nodiscard]] inline
Cross<L, R> cross(const Expr<L>& l, const Expr<L>& r) noexcept;

}

#include "cross_impl.hpp"
