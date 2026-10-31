#pragma once

#include "tenvex/detail/core/core.h"
#include "tenvex/detail/protocol/traits.h"
#include "tenvex/detail/protocol/concepts.h"

namespace tnvx
{

template<mat_expr E>
struct Determinant
{
	using result_t = vf4;

	TNVX_INLINE
	explicit Determinant(const E& TNVX_RESTRICT e) noexcept;

	[[nodiscard]] TNVX_INLINE
	result_t eval() const noexcept;

	[[nodiscard]] TNVX_INLINE
	operator float() const noexcept;

private:
	tnvx_ref_or_value_t<E> _e;
};

template<mat_expr E> inline constexpr bool is_scalar_expr<Determinant<E>> = true;

template<mat_expr E>
[[nodiscard]] TNVX_INLINE
Determinant<E> determinant(const E& m) noexcept;

}

#include "determinant_impl.hpp"
