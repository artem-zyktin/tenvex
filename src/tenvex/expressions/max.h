#pragma once

#include "core.h"
#include "expression.h"
#include "traits.h"
#include "concepts.h"

namespace tnvx
{

template<vec_expr L, vec_expr R>
struct Max : Expr<Max<L, R>>
{
	TNVX_INLINE
	Max(const L& TNVX_RESTRICT l, const R& TNVX_RESTRICT r) noexcept;

	[[nodiscard]] TNVX_INLINE
	vf4 eval() const noexcept;

private:
	tnvx_ref_or_value_t<L> _l;
	tnvx_ref_or_value_t<R> _r;
};

template<vec_expr L, vec_expr R> inline constexpr bool is_vec_expr<Max<L, R>> = true;

template<vec_expr L, vec_expr R>
[[nodiscard]] TNVX_INLINE
Max<L, R> max(const L& l, const R& r) noexcept;

}

#include "max_impl.hpp"
