#pragma once

#include "core.h"
#include "expression.h"
#include "traits.h"
#include "concepts.h"

namespace tnvx
{

template<quat_expr L, quat_expr R>
struct QuatMul : Expr<QuatMul<L, R>>
{

	TNVX_INLINE
	QuatMul(const L& TNVX_RESTRICT l, const R& TNVX_RESTRICT r) noexcept;

	[[nodiscard]] TNVX_INLINE
	vf4 eval() const noexcept;

private:
	tnvx_ref_or_value_t<L> _l;
	tnvx_ref_or_value_t<R> _r;
};

template<quat_expr L, quat_expr R> inline constexpr bool is_quat_expr<QuatMul<L, R>> = true;

template<quat_expr L, quat_expr R>
[[nodiscard]] TNVX_INLINE
QuatMul<L, R> operator*(const L& l, const R& r) noexcept;

}

#include "quat_mul_impl.hpp"
