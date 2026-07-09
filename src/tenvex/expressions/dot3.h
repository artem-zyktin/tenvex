#pragma once

#include "core.h"
#include "traits.h"
#include "concepts.h"

namespace tnvx
{

template<vec_expr L, vec_expr R>
struct Dot3
{
	using result_t = vf4;

	TNVX_INLINE
	Dot3(const L& TNVX_RESTRICT l, const R& TNVX_RESTRICT r) noexcept;

	[[nodiscard]] TNVX_INLINE
	result_t eval() const noexcept;

	[[nodiscard]] TNVX_INLINE
	operator float() const noexcept;

private:
	tnvx_ref_or_value_t<L> _l;
	tnvx_ref_or_value_t<R> _r;
};

template<vec_expr L, vec_expr R>
[[nodiscard]] TNVX_INLINE
Dot3<L, R> dot3(const L& l, const R& r) noexcept;

template<vec_expr L, vec_expr R> inline constexpr bool is_scalar_expr<Dot3<L, R>> = true;

}

#include "dot3_impl.hpp"
