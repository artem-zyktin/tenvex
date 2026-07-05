#pragma once

#include "rotate.h"

namespace tnvx
{

template<vec_expr V, quat_expr Q>
TNVX_INLINE
Rotate<V, Q>::Rotate(const V& TNVX_RESTRICT v, const Q& TNVX_RESTRICT q) noexcept
	: _v(v)
	, _q(q)
{
}

template<vec_expr V, quat_expr Q>
TNVX_INLINE
vf4 Rotate<V, Q>::eval() const noexcept
{
	return detail::rotate(_v.eval(), _q.eval());
}

template<vec_expr V, quat_expr Q>
TNVX_INLINE Rotate<V, Q> rotate(const V& v, const Q& q) noexcept
{
	return { v, q };
}

}
