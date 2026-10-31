#pragma once

#include "transform.h"

namespace tnvx
{

template<vec_expr V, mat_expr M>
TNVX_INLINE
Transform<V, M>::Transform(const V& TNVX_RESTRICT v, const M& TNVX_RESTRICT m) noexcept
	: _v(v)
	, _m(m)
{
}

template<vec_expr V, mat_expr M>
TNVX_INLINE
Transform<V, M>::result_t Transform<V, M>::eval() const noexcept
{
	return detail::mat_transform(_v.eval(), _m.eval());
}

template<vec_expr V, mat_expr M>
TNVX_INLINE
Transform<V, M> transform(const V& v, const M& m) noexcept
{
	return { v, m };
}

template<mat_expr M, vec_expr V>
TNVX_INLINE
Transform<V, M> operator*(const M& m, const V& v) noexcept
{
	return { v, m };
}

}
