#pragma once

#include "expressions/core/core.h"
#include "expressions/protocol/traits.h"
#include "expressions/protocol/concepts.h"

namespace tnvx
{

template<vec_expr E>
struct Floor
{
	using result_t = vf4;

	TNVX_INLINE
	explicit Floor(const E& TNVX_RESTRICT e) noexcept;

	[[nodiscard]] TNVX_INLINE
	result_t eval() const noexcept;

private:
	tnvx_ref_or_value_t<E> _e;
};

template<vec_expr E> inline constexpr bool is_vec_expr<Floor<E>> = true;

template<vec_expr E>
[[nodiscard]] TNVX_INLINE
Floor<E> floor(const E& e) noexcept;

}

#include "floor_impl.hpp"
