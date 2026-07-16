#pragma once

#include "tenvex/detail/core/core.h"
#include "tenvex/detail/protocol/traits.h"
#include "tenvex/detail/protocol/concepts.h"

namespace tnvx
{

template<vec_expr E>
struct Magn3
{
	using result_t = vf4;

	TNVX_INLINE
	explicit Magn3(const E& TNVX_RESTRICT e) noexcept;

	[[nodiscard]] TNVX_INLINE
	result_t eval() const noexcept;

	[[nodiscard]] TNVX_INLINE
	operator float() const noexcept;

	[[nodiscard]] TNVX_INLINE
	const E& operand() const noexcept;

private:
	tnvx_ref_or_value_t<E> _e;
};

template<vec_expr E>
TNVX_INLINE
Magn3<E> magnitude3(const E& e) noexcept;

template<vec_expr E> inline constexpr bool is_scalar_expr<Magn3<E>> = true;

}

#include "magnitude3_impl.hpp"
