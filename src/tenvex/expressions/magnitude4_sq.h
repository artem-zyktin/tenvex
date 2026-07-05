#pragma once

#include "core.h"
#include "expression.h"
#include "traits.h"
#include "concepts.h"

namespace tnvx
{

template<packed_expr E>
struct Magn4Sq : public Expr<Magn4Sq<E>>
{
	TNVX_INLINE
	explicit Magn4Sq(const E& TNVX_RESTRICT e) noexcept;

	[[nodiscard]] TNVX_INLINE
	vf4 eval() const noexcept;

	[[nodiscard]] TNVX_INLINE
	operator float() const noexcept;

private:
	tnvx_ref_or_value_t<E> _e;
};

template<packed_expr E> inline constexpr bool is_scalar_expr<Magn4Sq<E>> = true;

template<packed_expr E>
[[nodiscard]] TNVX_INLINE
Magn4Sq<E> magnitude4_sq(const E& e) noexcept;

}

#include "magnitude4_sq_impl.hpp"
