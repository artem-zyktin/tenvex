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

	[[nodiscard]] static mat4 look_at(vec4 eye, vec4 target, vec4 up) noexcept
	{
		const vec4 f = normalize3(target - eye);
		const vec4 s = normalize3(cross3(f, up));
		const vec4 u = cross3(s, f);

		return { s.x(), u.x(), -f.x(), 0.0f,
				 s.y(), u.y(), -f.y(), 0.0f,
				 s.z(), u.z(), -f.z(), 0.0f,
				 -dot3(s, eye), -dot3(u, eye), dot3(f, eye), 1.0f };
	}

	[[nodiscard]] static mat4 perspective(float fov_y, float aspect, float near_z, float far_z) noexcept
	{
		const float t = std::tan(fov_y * 0.5f);
		const float d = near_z - far_z;

		return { 1.0f / (aspect * t), 0.0f, 0.0f, 0.0f,
				 0.0f, 1.0f / t, 0.0f, 0.0f,
				 0.0f, 0.0f, far_z / d, -1.0f,
				 0.0f, 0.0f, far_z * near_z / d, 0.0f };
	}

	[[nodiscard]] static mat4 orthographic(float left, float right, float bottom, float top,
										   float near_z, float far_z) noexcept
	{
		const float w = right - left;
		const float h = top - bottom;
		const float d = far_z - near_z;

		return { 2.0f / w, 0.0f, 0.0f, 0.0f,
				 0.0f, 2.0f / h, 0.0f, 0.0f,
				 0.0f, 0.0f, -1.0f / d, 0.0f,
				 -(right + left) / w, -(top + bottom) / h, -near_z / d, 1.0f };
	}

private:
	vec4 _cols[4];
};

[[nodiscard]] inline mat4 operator+(const mat4& a, const mat4& b) noexcept
{
	return { a.col(0) + b.col(0), a.col(1) + b.col(1),
			 a.col(2) + b.col(2), a.col(3) + b.col(3) };
}

[[nodiscard]] inline mat4 operator-(const mat4& a, const mat4& b) noexcept
{
	return { a.col(0) - b.col(0), a.col(1) - b.col(1),
			 a.col(2) - b.col(2), a.col(3) - b.col(3) };
}

[[nodiscard]] inline mat4 operator-(const mat4& m) noexcept
{
	return { -m.col(0), -m.col(1), -m.col(2), -m.col(3) };
}

[[nodiscard]] inline mat4 operator*(const mat4& m, float s) noexcept
{
	return { m.col(0) * s, m.col(1) * s, m.col(2) * s, m.col(3) * s };
}

[[nodiscard]] inline mat4 operator*(float s, const mat4& m) noexcept
{
	return m * s;
}

[[nodiscard]] inline vec4 transform(vec4 v, const mat4& m) noexcept
{
	return m.col(0) * v.x() + m.col(1) * v.y()
		 + m.col(2) * v.z() + m.col(3) * v.w();
}

[[nodiscard]] inline vec4 operator*(const mat4& m, vec4 v) noexcept
{
	return transform(v, m);
}

[[nodiscard]] inline mat4 operator*(const mat4& a, const mat4& b) noexcept
{
	return { transform(b.col(0), a), transform(b.col(1), a),
			 transform(b.col(2), a), transform(b.col(3), a) };
}

[[nodiscard]] inline mat4 transpose(const mat4& m) noexcept
{
	return { m.at(0, 0), m.at(0, 1), m.at(0, 2), m.at(0, 3),
			 m.at(1, 0), m.at(1, 1), m.at(1, 2), m.at(1, 3),
			 m.at(2, 0), m.at(2, 1), m.at(2, 2), m.at(2, 3),
			 m.at(3, 0), m.at(3, 1), m.at(3, 2), m.at(3, 3) };
}

// Textbook cofactor expansion, unrolled over the sixteen elements and sharing
// the six 2x2 minors of each row pair. The packed kernel groups the same
// algebra as cross products over the columns (docs/decisions.md), so this is
// an independent check of it rather than a transcription.
//
// mRC is the element at row R, column C, matching the scalar constructor.
struct cofactors
{
	float m[4][4];   // m[r][c] is the minor left after striking row r, column c
	float det;
};

[[nodiscard]] inline cofactors expand(const mat4& x) noexcept
{
	const vec4 c0 = x.col(0);
	const vec4 c1 = x.col(1);
	const vec4 c2 = x.col(2);
	const vec4 c3 = x.col(3);

	const float m00 = c0.x(), m01 = c1.x(), m02 = c2.x(), m03 = c3.x();
	const float m10 = c0.y(), m11 = c1.y(), m12 = c2.y(), m13 = c3.y();
	const float m20 = c0.z(), m21 = c1.z(), m22 = c2.z(), m23 = c3.z();
	const float m30 = c0.w(), m31 = c1.w(), m32 = c2.w(), m33 = c3.w();

	// the six 2x2 minors of rows 2 and 3, then of rows 0 and 1
	const float s0 = m22 * m33 - m23 * m32;
	const float s1 = m21 * m33 - m23 * m31;
	const float s2 = m21 * m32 - m22 * m31;
	const float s3 = m20 * m33 - m23 * m30;
	const float s4 = m20 * m32 - m22 * m30;
	const float s5 = m20 * m31 - m21 * m30;

	const float t0 = m01 * m12 - m02 * m11;
	const float t1 = m01 * m13 - m03 * m11;
	const float t2 = m02 * m13 - m03 * m12;
	const float t3 = m00 * m12 - m02 * m10;
	const float t4 = m00 * m13 - m03 * m10;
	const float t5 = m00 * m11 - m01 * m10;

	cofactors r;
	r.m[0][0] = m11 * s0 - m12 * s1 + m13 * s2;
	r.m[0][1] = m10 * s0 - m12 * s3 + m13 * s4;
	r.m[0][2] = m10 * s1 - m11 * s3 + m13 * s5;
	r.m[0][3] = m10 * s2 - m11 * s4 + m12 * s5;

	r.m[1][0] = m01 * s0 - m02 * s1 + m03 * s2;
	r.m[1][1] = m00 * s0 - m02 * s3 + m03 * s4;
	r.m[1][2] = m00 * s1 - m01 * s3 + m03 * s5;
	r.m[1][3] = m00 * s2 - m01 * s4 + m02 * s5;

	r.m[2][0] = m31 * t2 - m32 * t1 + m33 * t0;
	r.m[2][1] = m30 * t2 - m32 * t4 + m33 * t3;
	r.m[2][2] = m30 * t1 - m31 * t4 + m33 * t5;
	r.m[2][3] = m30 * t0 - m31 * t3 + m32 * t5;

	r.m[3][0] = m21 * t2 - m22 * t1 + m23 * t0;
	r.m[3][1] = m20 * t2 - m22 * t4 + m23 * t3;
	r.m[3][2] = m20 * t1 - m21 * t4 + m23 * t5;
	r.m[3][3] = m20 * t0 - m21 * t3 + m22 * t5;

	r.det = m00 * r.m[0][0] - m01 * r.m[0][1] + m02 * r.m[0][2] - m03 * r.m[0][3];

	return r;
}

[[nodiscard]] inline float determinant(const mat4& x) noexcept
{
	return expand(x).det;
}

[[nodiscard]] inline mat4 inverse(const mat4& x) noexcept
{
	// the adjugate (cofactors transposed) over the determinant: column c of
	// the inverse holds the cofactors of row c, with the chequerboard signs
	const cofactors c = expand(x);
	const float d = 1.0f / c.det;

	return {  c.m[0][0] * d, -c.m[0][1] * d,  c.m[0][2] * d, -c.m[0][3] * d,
			 -c.m[1][0] * d,  c.m[1][1] * d, -c.m[1][2] * d,  c.m[1][3] * d,
			  c.m[2][0] * d, -c.m[2][1] * d,  c.m[2][2] * d, -c.m[2][3] * d,
			 -c.m[3][0] * d,  c.m[3][1] * d, -c.m[3][2] * d,  c.m[3][3] * d };
}

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