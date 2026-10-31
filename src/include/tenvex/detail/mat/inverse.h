#pragma once

#include "tenvex/detail/core/core.h"
#include "tenvex/detail/protocol/traits.h"
#include "tenvex/detail/protocol/concepts.h"

namespace tnvx
{

// MatInverse, not Inverse: that name belongs to the quaternion node. The two
// take disjoint operands, so the free function inverse() is shared.
template<mat_expr E>
struct MatInverse
{
	using result_t = mf4;

	TNVX_INLINE
	explicit MatInverse(const E& TNVX_RESTRICT e) noexcept;

	[[nodiscard]] TNVX_INLINE
	result_t eval() const noexcept;

private:
	tnvx_ref_or_value_t<E> _e;
};

template<mat_expr E> inline constexpr bool is_mat_expr<MatInverse<E>> = true;

template<mat_expr E>
[[nodiscard]] TNVX_INLINE
MatInverse<E> inverse(const E& m) noexcept;

}

#include "inverse_impl.hpp"
