#pragma once

#include "core.h"
#include "expression.h"
#include "concepts.h"
#include "traits.h"

namespace tnvx
{

template<vec_expr L, vec_expr R>
struct Sub : Expr<Sub<L, R>>
{
	TNVX_INLINE
	Sub(const L& TNVX_RESTRICT l, const R& TNVX_RESTRICT r) noexcept;

	[[nodiscard]] TNVX_INLINE
	vf4 eval() const noexcept;

private:
	tnvx_ref_or_value_t<L> _l;
	tnvx_ref_or_value_t<R> _r;
};

template<vec_expr L, vec_expr R>
[[nodiscard]] TNVX_INLINE
Sub<L, R> operator-(const L& l, const R& r) noexcept;

template<vec_expr L, vec_expr R> inline constexpr bool is_vec_expr<Sub<L, R>> = true;

}

#include "sub_impl.hpp"
