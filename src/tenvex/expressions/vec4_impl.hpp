#pragma once

#include "vec4.h"

namespace tnvx
{

TNVX_INLINE
vec4::vec4(float x, float y, float z, float w) noexcept
	: _data(_mm_set_ps(w, z, y, x))
{
}

TNVX_INLINE
__m128 vec4::eval() const noexcept
{
	return _data;
}

template<vec_expr E>
TNVX_INLINE
vec4::vec4(const E& TNVX_RESTRICT e) noexcept
	: _data(e.eval())
{
}

TNVX_INLINE
bool approx_eq(const vec4& lhs, const vec4& rhs, float eps) noexcept
{
	return detail::approx_eq(lhs.eval(), rhs.eval(), eps);
}

TNVX_INLINE
bool tnvx::operator==(const vec4& lhs, const vec4& rhs) noexcept
{
	return detail::eq(lhs.eval(), rhs.eval());
}

}
