#pragma once

#include "core.h"
#include "expression.h"
#include "traits.h"
#include "concepts.h"

namespace tnvx
{

template<expression E>
struct Neg : Expr<Neg<E>>
{
	using result_t = vf4;

	TNVX_INLINE
	explicit Neg(const E& TNVX_RESTRICT e) noexcept;

	[[nodiscard]] TNVX_INLINE
	result_t eval() const noexcept;

	[[nodiscard]] TNVX_INLINE
	operator float() const noexcept requires scalar_expr<E>;

private:
	tnvx_ref_or_value_t<E> _e;
};

template<vec_expr E> inline constexpr bool is_vec_expr<Neg<E>> = true;
template<scalar_expr E> inline constexpr bool is_scalar_expr<Neg<E>> = true;
template<quat_expr E> inline constexpr bool is_quat_expr<Neg<E>> = true;

template<expression E>
[[nodiscard]] TNVX_INLINE
Neg<E> operator-(const E& e) noexcept;

}

#include "neg_impl.hpp"
