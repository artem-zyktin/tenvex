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
vf4 vec4::eval() const noexcept
{
	return _data;
}

template<vec_expr E>
TNVX_INLINE
vec4::vec4(const E& e) noexcept
	: _data(e.eval())
{
}

TNVX_INLINE
bool approx_eq(const vec4& lhs, const vec4& rhs, float eps) noexcept
{
	return detail::approx_eq(lhs.eval(), rhs.eval(), eps);
}

TNVX_INLINE
bool operator==(const vec4& lhs, const vec4& rhs) noexcept
{
	return detail::eq(lhs.eval(), rhs.eval());
}

TNVX_INLINE
float vec4::x() const noexcept
{
	return detail::get_lane<0>(_data);
}

TNVX_INLINE
float vec4::y() const noexcept
{
	return detail::get_lane<1>(_data);
}

TNVX_INLINE
float vec4::z() const noexcept
{
	return detail::get_lane<2>(_data);
}

TNVX_INLINE
float vec4::w() const noexcept
{
	return detail::get_lane<3>(_data);
}

}
