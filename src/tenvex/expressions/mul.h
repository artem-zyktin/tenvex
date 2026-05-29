#pragma once

#include "defines.h"
#include "traits.h"
#include "expression.h"
#include "concepts.h"

#include "scalar.h"

#include <immintrin.h>

namespace tnvx
{

template<expression L, expression R>
struct Mul : Expr<Mul<L, R>>
{
	TNVX_INLINE
	Mul(const L& l, const R& r) noexcept;

	[[nodiscard]] TNVX_INLINE
	__m128 eval() const noexcept;

private:
	tnvx_ref_or_value_t<L> _l;
	tnvx_ref_or_value_t<R> _r;
};

template<vec_expr E>
[[nodiscard]] TNVX_INLINE
Mul<E, Scalar> operator*(const E& l, float r) noexcept;

template<vec_expr E>
[[nodiscard]] TNVX_INLINE
Mul<Scalar, E> operator*(float l, const E& r) noexcept;

template<scalar_expr L, scalar_expr R>
[[nodiscard]] TNVX_INLINE
Mul<L, R> operator*(const L& l, const R& r) noexcept;

template<vec_expr L, scalar_expr R> inline constexpr bool is_vec_expr<Mul<L, R>> = true;
template<scalar_expr L, vec_expr R> inline constexpr bool is_vec_expr<Mul<L, R>> = true;

template<scalar_expr L, scalar_expr R> inline constexpr bool is_scalar_expr<Mul<L, R>> = true;

}

#include "mul_impl.hpp"
