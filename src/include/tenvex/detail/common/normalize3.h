#pragma once

#include "tenvex/detail/core/core.h"
#include "tenvex/detail/protocol/traits.h"
#include "tenvex/detail/protocol/concepts.h"

namespace tnvx
{

template<packed_expr E>
struct Normalize3
{
	using result_t = vf4;

	TNVX_INLINE
	explicit Normalize3(const E& TNVX_RESTRICT e) noexcept;

	[[nodiscard]] TNVX_INLINE
	result_t eval() const noexcept;

private:
	tnvx_ref_or_value_t<E> _e;
};

template<packed_expr E>
[[nodiscard]] TNVX_INLINE
Normalize3<E> normalize3(const E& e) noexcept;

template<vec_expr E> inline constexpr bool is_vec_expr<Normalize3<E>> = true;
template<quat_expr E> inline constexpr bool is_quat_expr<Normalize3<E>> = true;

}
#include "normalize3_impl.hpp"
