#pragma once

#include "core.h"
#include "traits.h"
#include "concepts.h"

namespace tnvx
{

template<vec_expr E>
struct Magn3Sq
{
	using result_t = vf4;

	TNVX_INLINE
	explicit Magn3Sq(const E& TNVX_RESTRICT e) noexcept;

	[[nodiscard]] TNVX_INLINE
	result_t eval() const noexcept;

	[[nodiscard]] TNVX_INLINE
	operator float() const noexcept;

private:
	tnvx_ref_or_value_t<E> _e;
};

template<vec_expr E> inline constexpr bool is_scalar_expr<Magn3Sq<E>> = true;

template<vec_expr E>
[[nodiscard]] TNVX_INLINE
Magn3Sq<E> magnitude3_sq(const E& e) noexcept;

}

#include "magnitude3_sq_impl.hpp"
