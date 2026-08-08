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
	: _data({ { m00, m10, m20, m30 },
			  { m01, m11, m21, m31 },
			  { m02, m12, m22, m32 },
			  { m03, m13, m23, m33 } })
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

}
