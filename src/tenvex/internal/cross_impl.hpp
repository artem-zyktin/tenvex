#pragma once

#include "cross.h"

namespace tnvx
{

template<vector_expression L, vector_expression R>
TNVX_INLINE
Cross<L, R>::Cross(const L& TNVX_RESTRICT l, const R& TNVX_RESTRICT r) noexcept
	: _l(l)
	, _r(r)
{
}

template<vector_expression L, vector_expression R>
TNVX_INLINE
__m128 Cross<L, R>::eval() const noexcept
{
	__m128 a = _l.eval();
	__m128 b = _r.eval();

	// [ay, az, ax, 0]
	__m128 a_yzx = _mm_shuffle_ps(a, a, _MM_SHUFFLE(3, 0, 2, 1));
	// [by, bz, bx, 0]
	__m128 b_yzx = _mm_shuffle_ps(b, b, _MM_SHUFFLE(3, 0, 2, 1));

	// [ay*bz, az*bx, ax*by, 0]
	__m128 mul0 = _mm_mul_ps(a, b_yzx);
	// [az*by, ax*bz, ay*bx, 0]
	__m128 mul1 = _mm_mul_ps(a_yzx, b);

	// [ay*bz - az*by, az*bx - ax*bz, ax*by - ay*bx, 0]
	__m128 sub = _mm_sub_ps(mul0, mul1);

	// shuffle обратно в [x, y, z, 0]
	return _mm_shuffle_ps(sub, sub, _MM_SHUFFLE(3, 0, 2, 1));
}

template<vector_expression L, vector_expression R>
Cross<L, R> cross(const Expr<L>& l, const Expr<L>& r) noexcept
{
	return { l.self(), r.self() };
}


}
