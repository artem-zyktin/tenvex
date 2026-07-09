#pragma once

#include "core.h"
#include "expression.h"
#include "traits.h"
#include "concepts.h"

namespace tnvx
{

template<vec_expr E>
struct Magn3 : Expr<Magn3<E>>
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
