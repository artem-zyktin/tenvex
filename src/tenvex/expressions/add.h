#pragma once

#include "core.h"
#include "expression.h"
#include "concepts.h"
#include "traits.h"

#include "scalar.h"

namespace tnvx
{

template<expression L, expression R>
requires same_category<L, R>
struct Add : Expr<Add<L, R>>
{
	TNVX_INLINE
	Add(const L& TNVX_RESTRICT l, const R& TNVX_RESTRICT r) noexcept;

	[[nodiscard]] TNVX_INLINE
	vf4 eval() const noexcept;

	[[nodiscard]] TNVX_INLINE
	operator float() const noexcept
	requires scalar_expr<L> && scalar_expr<R>;

private:
	tnvx_ref_or_value_t<L> _l;
	tnvx_ref_or_value_t<R> _r;
};

template<vec_expr L, vec_expr R> inline constexpr bool is_vec_expr<Add<L, R>> = true;
template<scalar_expr L, scalar_expr R> inline constexpr bool is_scalar_expr<Add<L, R>> = true;

template<vec_expr L, vec_expr R>
[[nodiscard]] TNVX_INLINE
Add<L, R> operator+(const L& l, const R& r) noexcept;

template<scalar_expr L, scalar_expr R>
[[nodiscard]] TNVX_INLINE
Add<L, R> operator+(const L& l, const R& r) noexcept;

template<scalar_expr E>
[[nodiscard]] TNVX_INLINE
Add<E, Scalar> operator+(const E& l, float r) noexcept;

template<scalar_expr E>
[[nodiscard]] TNVX_INLINE
Add<Scalar, E> operator+(float l, const E& e) noexcept;

}

#include "add_impl.hpp"
