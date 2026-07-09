#pragma once

#include "expressions/core/core.h"
#include "expressions/protocol/traits.h"
#include "expressions/protocol/concepts.h"

namespace tnvx
{

template<packed_expr L, packed_expr R>
requires same_packed_category<L, R>
struct Dot4
{
	using result_t = vf4;

	TNVX_INLINE
	Dot4(const L& TNVX_RESTRICT l, const R& TNVX_RESTRICT r) noexcept;

	[[nodiscard]] TNVX_INLINE
	result_t eval() const noexcept;

	[[nodiscard]] TNVX_INLINE
	operator float() const noexcept;

private:
	tnvx_ref_or_value_t<L> _l;
	tnvx_ref_or_value_t<R> _r;
};

template<packed_expr L, packed_expr R>
requires same_packed_category<L, R> inline constexpr bool is_scalar_expr<Dot4<L, R>> = true;

template<packed_expr L, packed_expr R>
requires same_packed_category<L, R>
[[nodiscard]] TNVX_INLINE
Dot4<L, R> dot4(const L& l, const R& r) noexcept;

}

#include "dot4_impl.hpp"
