#pragma once

#include "core.h"
#include "expression.h"
#include "traits.h"
#include "concepts.h"

namespace tnvx
{

template<quat_expr E>
struct Inverse : Expr<Inverse<E>>
{
	using result_t = vf4;

	TNVX_INLINE
	explicit Inverse(const E& TNVX_RESTRICT e) noexcept;

	[[nodiscard]] TNVX_INLINE
	vf4 eval() const noexcept;

private:
	tnvx_ref_or_value_t<E> _e;
};

template<quat_expr E> inline constexpr bool is_quat_expr<Inverse<E>> = true;

template<quat_expr E>
[[nodiscard]] TNVX_INLINE
Inverse<E> inverse(const E& e) noexcept;

}

#include "inverse_impl.hpp"
