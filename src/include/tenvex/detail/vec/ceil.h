#pragma once

#include "tenvex/detail/core/core.h"
#include "tenvex/detail/protocol/traits.h"
#include "tenvex/detail/protocol/concepts.h"

namespace tnvx
{

template<vec_expr E>
struct Ceil
{
	using result_t = vf4;

	TNVX_INLINE
	explicit Ceil(const E& TNVX_RESTRICT e) noexcept;

	[[nodiscard]] TNVX_INLINE
	result_t eval() const noexcept;

private:
	tnvx_ref_or_value_t<E> _e;
};

template<vec_expr E> inline constexpr bool is_vec_expr<Ceil<E>> = true;

template<vec_expr E>
[[nodiscard]] TNVX_INLINE
Ceil<E> ceil(const E& e) noexcept;

}

#include "ceil_impl.hpp"
