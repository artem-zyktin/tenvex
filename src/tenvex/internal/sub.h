#pragma once

#include "expression.h"

namespace tnvx
{

template<expression L, expression R>
struct Sub : Expr<Sub<L, R>>
{
	inline
	Sub(const L& TNVX_RESTRICT l, const R& TNVX_RESTRICT r) noexcept;

	[[nodiscard]] inline
	__m128 eval() const noexcept;

private:
	tnvx_type_storage<L> _l;
	tnvx_type_storage<R> _r;
};

template<expression L, expression R>
[[nodiscard]] inline
Sub<L, R> operator-(const Expr<L>& l, const Expr<R>& r) noexcept;

}

#include "sub_impl.hpp"
