#pragma once

#include "tenvex/detail/core/core.h"
#include "tenvex/detail/protocol/traits.h"
#include "tenvex/detail/protocol/concepts.h"

namespace tnvx
{

template<mat_expr L, mat_expr R>
struct MatMul
{
	using result_t = mf4;

	TNVX_INLINE
	MatMul(const L& TNVX_RESTRICT l, const R& TNVX_RESTRICT r) noexcept;

	[[nodiscard]] TNVX_INLINE
	result_t eval() const noexcept;

private:
	tnvx_ref_or_value_t<L> _l;
	tnvx_ref_or_value_t<R> _r;
};

template<mat_expr L, mat_expr R> inline constexpr bool is_mat_expr<MatMul<L, R>> = true;

template<mat_expr L, mat_expr R>
[[nodiscard]] TNVX_INLINE
MatMul<L, R> operator*(const L& l, const R& r) noexcept;

}

#include "mat_mul_impl.hpp"
