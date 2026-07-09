#pragma once

#include "core.h"
#include "traits.h"
#include "concepts.h"

namespace tnvx
{

template<quat_expr E>
struct Conjugate
{
	using result_t = vf4;

	TNVX_INLINE
	explicit Conjugate(const E& TNVX_RESTRICT expr) noexcept;

	[[nodiscard]] TNVX_INLINE
	result_t eval() const noexcept;

private:
	tnvx_ref_or_value_t<E> _e;
};

template<quat_expr E> inline constexpr bool is_quat_expr<Conjugate<E>> = true;

template<quat_expr E>
[[nodiscard]] TNVX_INLINE
Conjugate<E> conjugate(const E& q) noexcept;

}

#include "conjugate_impl.hpp"
