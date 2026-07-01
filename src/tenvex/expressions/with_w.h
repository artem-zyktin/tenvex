#pragma once

#include "core.h"
#include "expression.h"
#include "concepts.h"
#include "traits.h"

namespace tnvx
{

template<vec_expr L, vec_expr R>
struct WithW : public Expr<WithW<L, R>>
{
	TNVX_INLINE
	WithW(const L& TNVX_RESTRICT l, const R& TNVX_RESTRICT r) noexcept;

	[[nodiscard]] TNVX_INLINE
	vf4 eval() const noexcept;

private:
	tnvx_ref_or_value_t<L> _l;
	tnvx_ref_or_value_t<R> _r;
};

template<vec_expr L, vec_expr R>
inline constexpr bool is_vec_expr<WithW<L, R>> = true;

template<vec_expr L, vec_expr R>
[[nodiscard]] TNVX_INLINE
WithW<L, R> with_w(const L& l, const R& r) noexcept;

}

#include "with_w_impl.hpp"
