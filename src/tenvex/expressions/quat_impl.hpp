#pragma once

#include "quat.h"

namespace tnvx
{

quat::quat(float x, float y, float z, float w) noexcept
	: _data(detail::set(x, y, z, w))
{
}

template<quat_expr E>
quat::quat(const E& e) noexcept
	: _data(e.eval())
{
}

TNVX_INLINE
vf4 quat::eval() const noexcept
{
	return _data;
}

TNVX_INLINE
float quat::x() const noexcept
{
	return detail::get_lane<0>(_data);
}

TNVX_INLINE
float quat::y() const noexcept
{
	return detail::get_lane<1>(_data);
}

TNVX_INLINE
float quat::z() const noexcept
{
	return detail::get_lane<2>(_data);
}

TNVX_INLINE
float quat::w() const noexcept
{
	return detail::get_lane<3>(_data);
}

TNVX_INLINE
bool approx_eq(const quat& lhs, const quat& rhs, float eps) noexcept
{
	return detail::approx_eq(lhs.eval(), rhs.eval(), eps);
}

TNVX_INLINE
bool operator==(const quat& lhs, const quat& rhs) noexcept
{
	return detail::eq(lhs.eval(), rhs.eval());
}

}
