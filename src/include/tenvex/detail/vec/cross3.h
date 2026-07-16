#pragma once

#include "tenvex/detail/core/core.h"
#include "tenvex/detail/protocol/traits.h"
#include "tenvex/detail/protocol/concepts.h"

namespace tnvx
{

template<vec_expr L, vec_expr R>
struct Cross3
{
	using result_t = vf4;

	TNVX_INLINE
	Cross3(const L& TNVX_RESTRICT l, const R& TNVX_RESTRICT r) noexcept;

	[[nodiscard]] TNVX_INLINE
	vf4 eval() const noexcept;

private:
	tnvx_ref_or_value_t<L> _l;
	tnvx_ref_or_value_t<R> _r;
};

template<vec_expr L, vec_expr R>
[[nodiscard]] TNVX_INLINE
Cross3<L, R> cross3(const L& l, const R& r) noexcept;

template<vec_expr L, vec_expr R> inline constexpr bool is_vec_expr<Cross3<L, R>> = true;

}

#include "cross3_impl.hpp"
