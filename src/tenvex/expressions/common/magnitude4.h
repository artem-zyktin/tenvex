#pragma once

#include "expressions/core/core.h"
#include "expressions/protocol/traits.h"
#include "expressions/protocol/concepts.h"

namespace tnvx
{

template<packed_expr E>
struct Magn4
{
	using result_t = vf4;

	TNVX_INLINE
	explicit Magn4(const E& TNVX_RESTRICT e) noexcept;

	[[nodiscard]] TNVX_INLINE
	result_t eval() const noexcept;

	[[nodiscard]] TNVX_INLINE
	operator float() const noexcept;

private:
	tnvx_ref_or_value_t<E> _e;
};

template<packed_expr E> inline constexpr bool is_scalar_expr<Magn4<E>> = true;

template<packed_expr E>
TNVX_INLINE
Magn4<E> magnitude4(const E& e) noexcept;

}

#include "magnitude4_impl.hpp"
