#pragma once

#include "core.h"
#include "concepts.h"
#include "traits.h"

#include "scalar.h"

namespace tnvx
{

template<expression L, expression R>
requires same_category<L, R>
struct Sub
{
	using result_t = vf4;

	TNVX_INLINE
	Sub(const L& TNVX_RESTRICT l, const R& TNVX_RESTRICT r) noexcept;

	[[nodiscard]] TNVX_INLINE
	result_t eval() const noexcept;

	[[nodiscard]] TNVX_INLINE
	operator float() const noexcept
	requires scalar_expr<L> && scalar_expr<R>;

private:
	tnvx_ref_or_value_t<L> _l;
	tnvx_ref_or_value_t<R> _r;
};

template<vec_expr L, vec_expr R> inline constexpr bool is_vec_expr<Sub<L, R>> = true;
template<scalar_expr L, scalar_expr R> inline constexpr bool is_scalar_expr<Sub<L, R>> = true;
template<quat_expr L, quat_expr R> inline constexpr bool is_quat_expr<Sub<L, R>> = true;

template<vec_expr L, vec_expr R>
[[nodiscard]] TNVX_INLINE
Sub<L, R> operator-(const L& l, const R& r) noexcept;

template<scalar_expr L, scalar_expr R>
[[nodiscard]] TNVX_INLINE
Sub<L, R> operator-(const L& l, const R& r) noexcept;

template<scalar_expr E>
[[nodiscard]] TNVX_INLINE
Sub<E, Scalar> operator-(const E& l, float r) noexcept;

template<scalar_expr E>
[[nodiscard]] TNVX_INLINE
Sub<Scalar, E> operator-(float l, const E& e) noexcept;

template<quat_expr L, quat_expr R>
[[nodiscard]] TNVX_INLINE
Sub<L, R> operator-(const L& l, const R& r) noexcept;

}

#include "sub_impl.hpp"
