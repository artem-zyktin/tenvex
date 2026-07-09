#pragma once

#include "core.h"
#include "expression.h"
#include "traits.h"
#include "concepts.h"

namespace tnvx
{

template<vec_expr L, vec_expr R>
struct Min : Expr<Min<L, R>>
{
	using result_t = vf4;

	TNVX_INLINE
	Min(const L& TNVX_RESTRICT l, const R& TNVX_RESTRICT r) noexcept;

	[[nodiscard]] TNVX_INLINE
	result_t eval() const noexcept;

private:
	tnvx_ref_or_value_t<L> _l;
	tnvx_ref_or_value_t<R> _r;
};

template<vec_expr L, vec_expr R> inline constexpr bool is_vec_expr<Min<L, R>> = true;

template<vec_expr L, vec_expr R>
[[nodiscard]] TNVX_INLINE
Min<L, R> min(const L& l, const R& r) noexcept;

}

#include "min_impl.hpp"
