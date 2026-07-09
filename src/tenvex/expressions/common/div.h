#pragma once

#include "expressions/core/core.h"
#include "expressions/protocol/traits.h"
#include "expressions/protocol/concepts.h"

#include "scalar.h"

namespace tnvx
{

template<packed_expr L, scalar_expr R>
struct Div
{
	using result_t = vf4;

	TNVX_INLINE
	Div(const L& TNVX_RESTRICT l, const R& TNVX_RESTRICT r) noexcept;

	[[nodiscard]] TNVX_INLINE
	result_t eval() const noexcept;

private:
	tnvx_ref_or_value_t<L> _l;
	tnvx_ref_or_value_t<R> _r;
};

template<packed_expr E>
[[nodiscard]] TNVX_INLINE
Div<E, Scalar> operator/(const E& l, float r) noexcept;

template<packed_expr L, scalar_expr R>
[[nodiscard]] TNVX_INLINE
Div<L, R> operator/(const L& l, const R& r) noexcept;

template<vec_expr L, scalar_expr R> inline constexpr bool is_vec_expr<Div<L, R>> = true;
template<quat_expr L, scalar_expr R> inline constexpr bool is_quat_expr<Div<L, R>> = true;

}

#include "div_impl.hpp"
