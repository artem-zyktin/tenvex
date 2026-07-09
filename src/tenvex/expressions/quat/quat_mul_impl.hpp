#pragma once

#include "quat_mul.h"

namespace tnvx
{

template<quat_expr L, quat_expr R>
TNVX_INLINE
QuatMul<L, R>::QuatMul(const L& TNVX_RESTRICT l, const R& TNVX_RESTRICT r) noexcept
	: _l(l), _r(r)
{
}

template<quat_expr L, quat_expr R>
TNVX_INLINE
QuatMul<L, R>::result_t QuatMul<L, R>::eval() const noexcept
{
	return detail::quat_mul(_l.eval(), _r.eval());
}

template<quat_expr L, quat_expr R>
TNVX_INLINE
QuatMul<L, R> operator*(const L& l, const R& r) noexcept
{
	return { l, r };
}

}
