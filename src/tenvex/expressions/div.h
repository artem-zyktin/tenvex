#pragma once

#include "core.h"
#include "expression.h"
#include "traits.h"
#include "concepts.h"

#include "scalar.h"

namespace tnvx
{

template<vec_expr L, scalar_expr R>
struct Div : Expr<Div<L, R>>
{
	TNVX_INLINE
	Div(const L& TNVX_RESTRICT l, const R& TNVX_RESTRICT r) noexcept;

	[[nodiscard]] TNVX_INLINE
	vf4 eval() const noexcept;

private:
	tnvx_ref_or_value_t<L> _l;
	tnvx_ref_or_value_t<R> _r;
};

template<vec_expr E>
[[nodiscard]] TNVX_INLINE
Div<E, Scalar> operator/(const E& l, float r) noexcept;

template<vec_expr L, scalar_expr R>
[[nodiscard]] TNVX_INLINE
Div<L, R> operator/(const L& l, const R& r) noexcept;

template<vec_expr L, scalar_expr R> inline constexpr bool is_vec_expr<Div<L, R>> = true;

}

#include "div_impl.hpp"
