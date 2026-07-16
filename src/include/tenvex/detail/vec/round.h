#pragma once

#include "tenvex/detail/core/core.h"
#include "tenvex/detail/protocol/traits.h"
#include "tenvex/detail/protocol/concepts.h"

namespace tnvx
{

template<vec_expr E>
struct Round
{
	using result_t = vf4;

	TNVX_INLINE
	explicit Round(const E& TNVX_RESTRICT e) noexcept;

	[[nodiscard]] TNVX_INLINE
	result_t eval() const noexcept;

private:
	tnvx_ref_or_value_t<E> _e;
};

template<vec_expr E> inline constexpr bool is_vec_expr<Round<E>> = true;

template<vec_expr E>
[[nodiscard]] TNVX_INLINE
Round<E> round(const E& e) noexcept;

}

#include "round_impl.hpp"
