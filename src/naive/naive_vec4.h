#pragma once

#include <cmath>

namespace naive
{

struct vec4
{
	vec4() noexcept = default;

	vec4(float x, float y, float z, float w = 0.0f) noexcept
		: _x(x), _y(y), _z(z), _w(w)
	{
	}

	[[nodiscard]] float x() const noexcept { return _x; }
	[[nodiscard]] float y() const noexcept { return _y; }
	[[nodiscard]] float z() const noexcept { return _z; }
	[[nodiscard]] float w() const noexcept { return _w; }

private:
	float _x, _y, _z, _w;
};

[[nodiscard]] inline vec4 operator+(vec4 a, vec4 b) noexcept
{
	return { a.x() + b.x(), a.y() + b.y(), a.z() + b.z(), a.w() + b.w() };
}

[[nodiscard]] inline vec4 operator-(vec4 a, vec4 b) noexcept
{
	return { a.x() - b.x(), a.y() - b.y(), a.z() - b.z(), a.w() - b.w() };
}

[[nodiscard]] inline vec4 operator*(vec4 v, float s) noexcept
{
	return { v.x() * s, v.y() * s, v.z() * s, v.w() * s };
}

[[nodiscard]] inline vec4 operator*(float s, vec4 v) noexcept
{
	return v * s;
}

[[nodiscard]] inline vec4 operator/(vec4 v, float s) noexcept
{
	const float inv = 1.0f / s;   // one division, then multiplies
	return { v.x() * inv, v.y() * inv, v.z() * inv, v.w() * inv };
}

[[nodiscard]] inline float dot3(vec4 a, vec4 b) noexcept
{
	return a.x() * b.x() + a.y() * b.y() + a.z() * b.z();
}

[[nodiscard]] inline vec4 cross3(vec4 a, vec4 b) noexcept
{
	return {
		a.y() * b.z() - a.z() * b.y(),
		a.z() * b.x() - a.x() * b.z(),
		a.x() * b.y() - a.y() * b.x(),
		0.0f
	};
}

[[nodiscard]] inline float magnitude3(vec4 v) noexcept
{
	return std::sqrt(dot3(v, v));
}

[[nodiscard]] inline vec4 norm3(vec4 v) noexcept
{
	const float inv = 1.0f / magnitude3(v);   // normalize xyz, keep w
	return { v.x() * inv, v.y() * inv, v.z() * inv, v.w() };
}

inline bool operator==(vec4 a, vec4 b) noexcept
{
	return a.x() == b.x() && a.y() == b.y()
		&& a.z() == b.z() && a.w() == b.w();
}

inline bool approx_eq(vec4 a, vec4 b, float eps = 1e-6f) noexcept
{
	return std::fabs(a.x() - b.x()) <= eps
		&& std::fabs(a.y() - b.y()) <= eps
		&& std::fabs(a.z() - b.z()) <= eps
		&& std::fabs(a.w() - b.w()) <= eps;
}

[[nodiscard]] inline vec4 operator-(vec4 v) noexcept
{
	return { -v.x(), -v.y(), -v.z(), -v.w() };
}

}