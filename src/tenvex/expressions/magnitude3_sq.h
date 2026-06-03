#pragma once

#include "core.h"
#include "expression.h"
#include "traits.h"
#include "concepts.h"

namespace tnvx
{

template<vec_expr E>
struct Magn3Sq : Expr<Magn3Sq<E>>
{
	TNVX_INLINE
	explicit Magn3Sq(const E& e) noexcept;

	[[nodiscard]] TNVX_INLINE
	vf4 eval() const noexcept;

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
