#pragma once

#include "core.h"
#include "expression.h"
#include "traits.h"
#include "concepts.h"

namespace tnvx
{

template<vec_expr V, quat_expr Q>
struct Rotate : Expr<Rotate<V, Q>>
{
	using result_t = vf4;

	TNVX_INLINE
	Rotate(const V& TNVX_RESTRICT v, const Q& TNVX_RESTRICT q) noexcept;

	[[nodiscard]] TNVX_INLINE
	result_t eval() const noexcept;

private:
	tnvx_ref_or_value_t<V> _v;
	tnvx_ref_or_value_t<Q> _q;
};

template<vec_expr V, quat_expr Q> inline constexpr bool is_vec_expr<Rotate<V, Q>> = true;

template<vec_expr V, quat_expr Q>
[[nodiscard]] TNVX_INLINE
Rotate<V, Q> rotate(const V& v, const Q& q) noexcept;

}

#include "rotate_impl.hpp"
