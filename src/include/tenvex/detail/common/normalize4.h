#pragma once

#include "tenvex/detail/core/core.h"
#include "tenvex/detail/protocol/traits.h"
#include "tenvex/detail/protocol/concepts.h"

namespace tnvx
{

template<packed_expr E>
struct Normalize4
{
	using result_t = vf4;

	TNVX_INLINE
	explicit Normalize4(const E& TNVX_RESTRICT e) noexcept;

	[[nodiscard]] TNVX_INLINE
	result_t eval() const noexcept;

private:
	tnvx_ref_or_value_t<E> _e;
};

template<vec_expr E> inline constexpr bool is_vec_expr<Normalize4<E>> = true;
template<quat_expr E> inline constexpr bool is_quat_expr<Normalize4<E>> = true;

template<packed_expr E>
Normalize4<E> normalize4(const E& e) noexcept;

}

#include "normalize4_impl.hpp"
