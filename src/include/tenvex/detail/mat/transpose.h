#pragma once

#include "tenvex/detail/core/core.h"
#include "tenvex/detail/protocol/traits.h"
#include "tenvex/detail/protocol/concepts.h"

namespace tnvx
{

template<mat_expr E>
struct Transpose
{
	using result_t = mf4;

	TNVX_INLINE
	explicit Transpose(const E& TNVX_RESTRICT e) noexcept;

	[[nodiscard]] TNVX_INLINE
	result_t eval() const noexcept;

private:
	tnvx_ref_or_value_t<E> _e;
};

template<mat_expr E> inline constexpr bool is_mat_expr<Transpose<E>> = true;

template<mat_expr E>
[[nodiscard]] TNVX_INLINE
Transpose<E> transpose(const E& m) noexcept;

}

#include "transpose_impl.hpp"
