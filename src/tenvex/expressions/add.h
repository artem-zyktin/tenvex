#pragma once

#include "defines.h"
#include "expression.h"
#include "concepts.h"
#include "traits.h"

#include <immintrin.h>

namespace tnvx
{

template<vec_expr L, vec_expr R>
struct Add : Expr<Add<L, R>>
{
	TNVX_INLINE
	Add(const L& TNVX_RESTRICT l, const R& TNVX_RESTRICT r) noexcept;

	[[nodiscard]] TNVX_INLINE
	__m128 eval() const noexcept;

private:
	tnvx_ref_or_value_t<L> _l;
	tnvx_ref_or_value_t<L> _r;
};

template<vec_expr L, vec_expr R>
[[nodiscard]] TNVX_INLINE
Add<L, R> operator+(const L& l, const R& r) noexcept;

template<vec_expr L, vec_expr R>
inline constexpr bool is_vec_expr<Add<L, R>> = true;

}

#include "add_impl.hpp"
