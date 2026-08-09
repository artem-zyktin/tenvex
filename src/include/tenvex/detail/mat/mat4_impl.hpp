#pragma once

#include "mat4.h"

#include "tenvex/detail/vec/with_w.h"
#include "tenvex/detail/vec/hadamard.h"

namespace tnvx
{

TNVX_INLINE
mat4::mat4(float m00, float m10, float m20, float m30,
		   float m01, float m11, float m21, float m31,
		   float m02, float m12, float m22, float m32,
		   float m03, float m13, float m23, float m33) noexcept
	: _data({ detail::set(m00, m10, m20, m30),
			  detail::set(m01, m11, m21, m31),
			  detail::set(m02, m12, m22, m32),
			  detail::set(m03, m13, m23, m33) })
{
}

template<mat_expr E>
TNVX_INLINE
mat4::mat4(const E& e) noexcept
	: _data(e.eval())
{
}

TNVX_INLINE
mat4::mat4(vf4 col0, vf4 col1, vf4 col2, vf4 col3) noexcept
	: _data({ col0, col1, col2, col3 })
{
}

TNVX_INLINE
mat4::mat4(vec4 col0, vec4 col1, vec4 col2, vec4 col3) noexcept
	: _data({ col0.eval(), col1.eval(), col2.eval(), col3.eval() })
{
}

TNVX_INLINE
mat4 mat4::zero() noexcept
{
	return { 0.0f, 0.0f, 0.0f, 0.0f,
			 0.0f, 0.0f, 0.0f, 0.0f,
			 0.0f, 0.0f, 0.0f, 0.0f,
			 0.0f, 0.0f, 0.0f, 0.0f };
}

TNVX_INLINE
mat4 mat4::identity() noexcept
{
	return { 1.0f, 0.0f, 0.0f, 0.0f,
			 0.0f, 1.0f, 0.0f, 0.0f,
			 0.0f, 0.0f, 1.0f, 0.0f,
			 0.0f, 0.0f, 0.0f, 1.0f };
}

TNVX_INLINE
mat4::mat4(const mf4& data) noexcept
	: _data(data)
{
}

TNVX_INLINE
mat4 mat4::translation(const vec4& t) noexcept
{
	return { vec4::unit_x(), vec4::unit_y(), vec4::unit_z(), with_w(t, vec4::one()) };
}

TNVX_INLINE
mat4 mat4::translation(float x, float y, float z) noexcept
{
	return translation(vec4 { x, y, z, 1.0f });
}

TNVX_INLINE
mat4 mat4::scaling(float x, float y, float z) noexcept
{
	return {    x, 0.0f, 0.0f, 0.0f,
			 0.0f,    y, 0.0f, 0.0f,
			 0.0f, 0.0f,    z, 0.0f,
			 0.0f, 0.0f, 0.0f, 1.0f };
}

TNVX_INLINE
mat4 mat4::scaling(float s) noexcept
{
	return scaling(s, s, s);
}

TNVX_INLINE
mat4 mat4::scaling(const vec4& s) noexcept
{
	return { hadamard(vec4::unit_x(), s),
			 hadamard(vec4::unit_y(), s),
			 hadamard(vec4::unit_z(), s),
			 vec4::unit_w() };
}

TNVX_INLINE
mat4 mat4::from_quat(const quat& q) noexcept
{
	return mat4( detail::mat_from_quat(q.eval()) );
}

TNVX_INLINE
mat4 mat4::from_rotation(const vec4& axis, float angle) noexcept
{
	return from_quat(quat::from_axis_angle(axis, angle));
}

TNVX_INLINE
vec4 mat4::col(int j) const noexcept
{
	return vec4{ _data.cols[j] };
}

template<uint8_t i, uint8_t j>
TNVX_INLINE
float mat4::at() const noexcept
{
	static_assert(i < 4, "row index out of range");
	static_assert(j < 4, "column index out of range");

	return detail::get_lane<i>(_data.cols[j]);
}

TNVX_INLINE
mat4::result_t mat4::eval() const noexcept
{
	return _data;
}

TNVX_INLINE
bool approx_eq(const mat4& lhs, const mat4& rhs, float eps) noexcept
{
	const mf4 l = lhs.eval();
	const mf4 r = rhs.eval();

	return detail::approx_eq(l.cols[0], r.cols[0], eps)
		&& detail::approx_eq(l.cols[1], r.cols[1], eps)
		&& detail::approx_eq(l.cols[2], r.cols[2], eps)
		&& detail::approx_eq(l.cols[3], r.cols[3], eps);
}

TNVX_INLINE
bool operator==(const mat4& lhs, const mat4& rhs) noexcept
{
	const mf4 l = lhs.eval();
	const mf4 r = rhs.eval();

	return detail::eq(l.cols[0], r.cols[0])
		&& detail::eq(l.cols[1], r.cols[1])
		&& detail::eq(l.cols[2], r.cols[2])
		&& detail::eq(l.cols[3], r.cols[3]);
}

}
