#pragma once

#include "naive_quat.h"

#include <cmath>

namespace naive
{

struct mat4
{
	mat4() noexcept = default;

	mat4(float m00, float m10, float m20, float m30,
		 float m01, float m11, float m21, float m31,
		 float m02, float m12, float m22, float m32,
		 float m03, float m13, float m23, float m33) noexcept
		: _cols{ { m00, m10, m20, m30 },
				 { m01, m11, m21, m31 },
				 { m02, m12, m22, m32 },
				 { m03, m13, m23, m33 } }
	{
	}

	mat4(vec4 col0, vec4 col1, vec4 col2, vec4 col3) noexcept
		: _cols{ col0, col1, col2, col3 }
	{
	}

	[[nodiscard]] vec4 col(int j) const noexcept { return _cols[j]; }

	[[nodiscard]] float at(int i, int j) const noexcept
	{
		const vec4 c = _cols[j];

		switch (i)
		{
			case 0:  return c.x();
			case 1:  return c.y();
			case 2:  return c.z();
			default: return c.w();
		}
	}

	[[nodiscard]] static mat4 zero() noexcept
	{
		return { 0.0f, 0.0f, 0.0f, 0.0f,
				 0.0f, 0.0f, 0.0f, 0.0f,
				 0.0f, 0.0f, 0.0f, 0.0f,
				 0.0f, 0.0f, 0.0f, 0.0f };
	}

	[[nodiscard]] static mat4 identity() noexcept
	{
		return { 1.0f, 0.0f, 0.0f, 0.0f,
				 0.0f, 1.0f, 0.0f, 0.0f,
				 0.0f, 0.0f, 1.0f, 0.0f,
				 0.0f, 0.0f, 0.0f, 1.0f };
	}

	[[nodiscard]] static mat4 translation(vec4 t) noexcept
	{
		return {  1.0f,   0.0f,   0.0f, 0.0f,
				  0.0f,   1.0f,   0.0f, 0.0f,
				  0.0f,   0.0f,   1.0f, 0.0f,
				 t.x(),  t.y(),  t.z(), 1.0f };
	}

	[[nodiscard]] static mat4 translation(float x, float y, float z) noexcept
	{
		return translation(vec4 { x, y, z, 1.0f });
	}

	[[nodiscard]] static mat4 scaling(float x, float y, float z) noexcept
	{
		return {    x, 0.0f, 0.0f, 0.0f,
				 0.0f,    y, 0.0f, 0.0f,
				 0.0f, 0.0f,    z, 0.0f,
				 0.0f, 0.0f, 0.0f, 1.0f };
	}

	[[nodiscard]] static mat4 scaling(float s) noexcept
	{
		return scaling(s, s, s);
	}

	[[nodiscard]] static mat4 scaling(vec4 s) noexcept
	{
		return scaling(s.x(), s.y(), s.z());
	}

	[[nodiscard]] static mat4 from_quat(quat q) noexcept
	{
		const float x = q.x();
		const float y = q.y();
		const float z = q.z();
		const float w = q.w();

		// column j = rotated basis vector e_j
		return { 1.0f - 2.0f * (y * y + z * z),
				 2.0f * (x * y + w * z),
				 2.0f * (x * z - w * y),
				 0.0f,

				 2.0f * (x * y - w * z),
				 1.0f - 2.0f * (x * x + z * z),
				 2.0f * (y * z + w * x),
				 0.0f,

				 2.0f * (x * z + w * y),
				 2.0f * (y * z - w * x),
				 1.0f - 2.0f * (x * x + y * y),
				 0.0f,

				 0.0f, 0.0f, 0.0f, 1.0f };
	}

	[[nodiscard]] static mat4 from_rotation(vec4 axis, float angle) noexcept
	{
		return from_quat(quat::from_axis_angle(axis, angle));
	}

private:
	vec4 _cols[4];
};

inline bool operator==(const mat4& a, const mat4& b) noexcept
{
	return a.col(0) == b.col(0) && a.col(1) == b.col(1)
		&& a.col(2) == b.col(2) && a.col(3) == b.col(3);
}

inline bool approx_eq(const mat4& a, const mat4& b, float eps = 1e-6f) noexcept
{
	return approx_eq(a.col(0), b.col(0), eps)
		&& approx_eq(a.col(1), b.col(1), eps)
		&& approx_eq(a.col(2), b.col(2), eps)
		&& approx_eq(a.col(3), b.col(3), eps);
}

}