#pragma once

#include "tenvex/detail/core/core.h"
#include "tenvex/detail/protocol/traits.h"
#include "tenvex/detail/protocol/concepts.h"

namespace tnvx
{

template<vec_expr L, vec_expr R>
struct Hadamard
{
	using result_t = vf4;

	TNVX_INLINE
	Hadamard(const L& TNVX_RESTRICT l, const R& TNVX_RESTRICT r) noexcept;

	[[nodiscard]] TNVX_INLINE
	result_t eval() const noexcept;

private:
	tnvx_ref_or_value_t<L> _l;
	tnvx_ref_or_value_t<R> _r;
};

template<vec_expr L, vec_expr R> inline constexpr bool is_vec_expr<Hadamard<L, R>> = true;

template<vec_expr L, vec_expr R>
[[nodiscard]] TNVX_INLINE
Hadamard<L, R> hadamard(const L& l, const R& r) noexcept;

}

#include "hadamard_impl.hpp"
