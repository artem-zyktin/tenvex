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
quat::quat(vf4 value) noexcept
	: _data(value)
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

template<mat_expr M>
TNVX_INLINE quat quat::from_mat(const M& m) noexcept
{
	// mRC is the element at row R, column C; only the upper-left 3x3 is read,
	// and the matrix is assumed to be a rotation (orthonormal, det +1) - the
	// precondition mirrors the unit-quaternion one on mat4::from_quat.
	const mf4 r = m.eval();

	const float m00 = detail::get_lane<0>(r.cols[0]);
	const float m10 = detail::get_lane<1>(r.cols[0]);
	const float m20 = detail::get_lane<2>(r.cols[0]);
	const float m01 = detail::get_lane<0>(r.cols[1]);
	const float m11 = detail::get_lane<1>(r.cols[1]);
	const float m21 = detail::get_lane<2>(r.cols[1]);
	const float m02 = detail::get_lane<0>(r.cols[2]);
	const float m12 = detail::get_lane<1>(r.cols[2]);
	const float m22 = detail::get_lane<2>(r.cols[2]);

	// 4x^2, 4y^2, 4z^2 and 4w^2. They sum to 4, so the largest is at least 1:
	// taking the square root of that one and dividing the rest by it keeps the
	// small components out of a cancelling subtraction.
	const float xx = 1.0f + m00 - m11 - m22;
	const float yy = 1.0f - m00 + m11 - m22;
	const float zz = 1.0f - m00 - m11 + m22;
	const float ww = 1.0f + m00 + m11 + m22;

	if (ww > xx && ww > yy && ww > zz)
	{
		const float s = std::sqrt(ww);
		const float k = 0.5f / s;
		return { (m21 - m12) * k, (m02 - m20) * k, (m10 - m01) * k, 0.5f * s };
	}

	if (xx > yy && xx > zz)
	{
		const float s = std::sqrt(xx);
		const float k = 0.5f / s;
		return { 0.5f * s, (m01 + m10) * k, (m02 + m20) * k, (m21 - m12) * k };
	}

	if (yy > zz)
	{
		const float s = std::sqrt(yy);
		const float k = 0.5f / s;
		return { (m01 + m10) * k, 0.5f * s, (m12 + m21) * k, (m02 - m20) * k };
	}

	const float s = std::sqrt(zz);
	const float k = 0.5f / s;
	return { (m02 + m20) * k, (m12 + m21) * k, 0.5f * s, (m10 - m01) * k };
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
