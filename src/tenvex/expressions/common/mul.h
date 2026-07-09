#pragma once

#include "expressions/core/core.h"
#include "expressions/protocol/traits.h"
#include "expressions/protocol/concepts.h"

#include "scalar.h"

namespace tnvx
{

template<expression L, expression R>
requires scalable<L, R>
struct Mul
{
	using result_t = vf4;

	TNVX_INLINE
	Mul(const L& TNVX_RESTRICT l, const R& TNVX_RESTRICT r) noexcept;

	[[nodiscard]] TNVX_INLINE
	result_t eval() const noexcept;

private:
	tnvx_ref_or_value_t<L> _l;
	tnvx_ref_or_value_t<R> _r;
};

template<vec_expr L, scalar_expr R> inline constexpr bool is_vec_expr<Mul<L, R>> = true;
template<scalar_expr L, vec_expr R> inline constexpr bool is_vec_expr<Mul<L, R>> = true;
template<quat_expr L, scalar_expr R> inline constexpr bool is_quat_expr<Mul<L, R>> = true;
template<scalar_expr L, quat_expr R> inline constexpr bool is_quat_expr<Mul<L, R>> = true;
template<scalar_expr L, scalar_expr R> inline constexpr bool is_scalar_expr<Mul<L, R>> = true;

// this bunch of reloads (instead of expression*expression)  is required for two things:
// 1. to avoid ambiguity with operator* for vector-vector multiplication
// 2. to avoid scalar operator collapses to float instead of lazy-expressions


template<vec_expr E>
[[nodiscard]] TNVX_INLINE
Mul<E, Scalar> operator*(const E& l, float r) noexcept;

template<vec_expr E>
[[nodiscard]] TNVX_INLINE
Mul<Scalar, E> operator*(float l, const E& r) noexcept;

template<scalar_expr L, scalar_expr R>
[[nodiscard]] TNVX_INLINE
Mul<L, R> operator*(const L& l, const R& r) noexcept;

template<scalar_expr L, vec_expr R>
[[nodiscard]] TNVX_INLINE
Mul<L, R> operator*(const L& l, const R& r) noexcept;

template<vec_expr L, scalar_expr R>
[[nodiscard]] TNVX_INLINE
Mul<L, R> operator*(const L& l, const R& r) noexcept;

template<quat_expr E>
[[nodiscard]] TNVX_INLINE
Mul<Scalar, E> operator*(float l, const E& r) noexcept;

template<quat_expr E>
[[nodiscard]] TNVX_INLINE
Mul<E, Scalar> operator*(const E& l, float r) noexcept;

template<quat_expr L, scalar_expr R>
[[nodiscard]] TNVX_INLINE
Mul<L, R> operator*(const L& l, const R& r) noexcept;

template<scalar_expr L, quat_expr R>
[[nodiscard]] TNVX_INLINE
Mul<L, R> operator*(const L& l, const R& r) noexcept;

template<scalar_expr E>
[[nodiscard]] TNVX_INLINE
Mul<E, Scalar> operator*(const E& l, float r) noexcept;

template<scalar_expr E>
[[nodiscard]] TNVX_INLINE
Mul<Scalar, E> operator*(float l, const E& r) noexcept;

}

#include "mul_impl.hpp"
