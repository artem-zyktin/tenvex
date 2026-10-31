#pragma once

#include "tenvex/detail/core/core.h"
#include "tenvex/detail/protocol/traits.h"
#include "tenvex/detail/protocol/concepts.h"

namespace tnvx
{

// M * v. The named form keeps the verb(object, argument) order of rotate(v, q)
// and is unrelated to the operator convention; both build this node.
template<vec_expr V, mat_expr M>
struct Transform
{
	using result_t = vf4;

	TNVX_INLINE
	Transform(const V& TNVX_RESTRICT v, const M& TNVX_RESTRICT m) noexcept;

	[[nodiscard]] TNVX_INLINE
	result_t eval() const noexcept;

private:
	tnvx_ref_or_value_t<V> _v;
	tnvx_ref_or_value_t<M> _m;
};

template<vec_expr V, mat_expr M> inline constexpr bool is_vec_expr<Transform<V, M>> = true;

template<vec_expr V, mat_expr M>
[[nodiscard]] TNVX_INLINE
Transform<V, M> transform(const V& v, const M& m) noexcept;

template<mat_expr M, vec_expr V>
[[nodiscard]] TNVX_INLINE
Transform<V, M> operator*(const M& m, const V& v) noexcept;

}

#include "transform_impl.hpp"
