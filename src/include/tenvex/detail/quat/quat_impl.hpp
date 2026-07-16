#pragma once

#include "quat.h"

#include "tenvex/detail/vec.h"

#include <cmath>

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
quat::result_t quat::eval() const noexcept
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

TNVX_INLINE quat quat::identity() noexcept
{
	return { 0.0f, 0.0f, 0.0f, 1.0f };
}

TNVX_INLINE quat quat::from_axis_angle(float ax, float ay, float az, float angle) noexcept
{
	const float half = angle * 0.5f;
	const float c = std::cos(half);
	float s = std::sin(half);

	const float len = std::sqrt(ax * ax + ay * ay + az * az);
	float inv = len > 0.f ? 1.f / len : 0.f;
	s *= inv;

	return { ax * s, ay * s, az * s, c };
}

TNVX_INLINE quat quat::from_axis_angle(vec4 asix, float angle) noexcept
{
	return from_axis_angle(asix.x(), asix.y(), asix.z(), angle);
}

TNVX_INLINE quat quat::from_to_rotation(vec4 from, vec4 to) noexcept
{
	vec4 f = normalize3(from);
	vec4 t = normalize3(to);

	float d = dot3(f, t);

	if (d < -0.999999f)
	{
		vec4 orth = orthogonal(f);
		vec4 axis = orth / magnitude3(orth);
		return { axis.x(), axis.y(), axis.z(), 0.f};
	}

	vec4 c = cross3(f, t);
	float w = 1.f + d;
	return normalize4(quat { c.x(), c.y(), c.z(), w});
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
