#pragma once

#include "core.h"
#include "expression.h"
#include "traits.h"
#include "concepts.h"

#include "scalar.h"

namespace tnvx
{

template<expression L, expression R>
struct Mul : Expr<Mul<L, R>>
{
	TNVX_INLINE
	Mul(const L& TNVX_RESTRICT l, const R& TNVX_RESTRICT r) noexcept;

	[[nodiscard]] TNVX_INLINE
	vf4 eval() const noexcept;

private:
	tnvx_ref_or_value_t<L> _l;
	tnvx_ref_or_value_t<R> _r;
};

template<vec_expr E>
[[nodiscard]] TNVX_INLINE
Mul<E, Scalar> operator*(const E& TNVX_RESTRICT l, float r) noexcept;

template<vec_expr E>
[[nodiscard]] TNVX_INLINE
Mul<Scalar, E> operator*(float l, const E& TNVX_RESTRICT r) noexcept;

template<scalar_expr L, scalar_expr R>
[[nodiscard]] TNVX_INLINE
Mul<L, R> operator*(const L& TNVX_RESTRICT l, const R& TNVX_RESTRICT r) noexcept;

template<vec_expr L, scalar_expr R> inline constexpr bool is_vec_expr<Mul<L, R>> = true;
template<scalar_expr L, vec_expr R> inline constexpr bool is_vec_expr<Mul<L, R>> = true;

template<scalar_expr L, scalar_expr R> inline constexpr bool is_scalar_expr<Mul<L, R>> = true;

}

#include "mul_impl.hpp"
