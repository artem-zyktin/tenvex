#pragma once

#include <cmath>
#include <algorithm>

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

	[[nodiscard]] static vec4 zero() noexcept { return { 0.0f, 0.0f, 0.0f, 0.0f }; }
	[[nodiscard]] static vec4 one() noexcept { return { 1.0f, 1.0f, 1.0f, 1.0f }; }
	[[nodiscard]] static vec4 unit_x() noexcept { return { 1.0f, 0.0f, 0.0f, 0.0f }; }
	[[nodiscard]] static vec4 unit_y() noexcept { return { 0.0f, 1.0f, 0.0f, 0.0f }; }
	[[nodiscard]] static vec4 unit_z() noexcept { return { 0.0f, 0.0f, 1.0f, 0.0f }; }
	[[nodiscard]] static vec4 unit_w() noexcept { return { 0.0f, 0.0f, 0.0f, 1.0f }; }
	[[nodiscard]] static vec4 splat(float s) noexcept { return { s, s, s, s }; }

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

[[nodiscard]] inline vec4 abs(vec4 v) noexcept
{
	return {
		std::fabs(v.x()),
		std::fabs(v.y()),
		std::fabs(v.z()),
		std::fabs(v.w())
	};
}

[[nodiscard]] inline float dot3(vec4 a, vec4 b) noexcept
{
	return a.x() * b.x() + a.y() * b.y() + a.z() * b.z();
}

[[nodiscard]] inline float dot4(vec4 a, vec4 b) noexcept
{
	return a.x() * b.x() + a.y() * b.y() + a.z() * b.z() + a.w() * b.w();
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

[[nodiscard]] inline float magnitude3_sq(vec4 v) noexcept
{
	return dot3(v, v);
}

[[nodiscard]] inline vec4 normalize3(vec4 v) noexcept
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

[[nodiscard]] inline vec4 min(vec4 a, vec4 b) noexcept
{
	return {
		std::min(a.x(), b.x()),
		std::min(a.y(), b.y()),
		std::min(a.z(), b.z()),
		std::min(a.w(), b.w())
	};
}

[[nodiscard]] inline vec4 max(vec4 a, vec4 b) noexcept
{
	return {
		std::max(a.x(), b.x()),
		std::max(a.y(), b.y()),
		std::max(a.z(), b.z()),
		std::max(a.w(), b.w())
	};
}

[[nodiscard]] inline vec4 clamp(vec4 v, vec4 lo, vec4 hi) noexcept
{
	return min(max(v, lo), hi);
}

[[nodiscard]] inline vec4 saturate(vec4 v) noexcept
{
	return clamp(v, vec4 { 0.0f, 0.0f, 0.0f, 0.0f }, vec4 { 1.0f, 1.0f, 1.0f, 1.0f });
}

[[nodiscard]] inline vec4 lerp(vec4 a, vec4 b, float t) noexcept
{
	return a + (b - a) * t;
}

[[nodiscard]] inline float distance3(vec4 l, vec4 r) noexcept
{
	return magnitude3(l - r);
}

[[nodiscard]] inline float distance3_sq(vec4 l, vec4 r) noexcept
{
	return magnitude3_sq(l - r);
}

[[nodiscard]] inline vec4 reflect(vec4 v, vec4 n) noexcept
{
	return v - n * (dot3(v, n) * 2.0f);
}

[[nodiscard]] inline vec4 floor(vec4 v) noexcept
{
	return { std::floor(v.x()), std::floor(v.y()), std::floor(v.z()), std::floor(v.w()) };
}

[[nodiscard]] inline vec4 ceil(vec4 v) noexcept
{
	return { std::ceil(v.x()), std::ceil(v.y()), std::ceil(v.z()), std::ceil(v.w()) };
}

[[nodiscard]] inline vec4 round(vec4 v) noexcept
{
	return { std::nearbyint(v.x()), std::nearbyint(v.y()), std::nearbyint(v.z()), std::nearbyint(v.w()) };
}

[[nodiscard]] inline vec4 frac(vec4 v) noexcept
{
	return { v.x() - std::floor(v.x()), v.y() - std::floor(v.y()),
			 v.z() - std::floor(v.z()), v.w() - std::floor(v.w()) };
}

[[nodiscard]] inline vec4 hadamard(vec4 a, vec4 b) noexcept
{
	return { a.x() * b.x(), a.y() * b.y(), a.z() * b.z(), a.w() * b.w() };
}

[[nodiscard]] inline float magnitude4(vec4 v) noexcept
{
	return std::sqrt(dot4(v, v));
}

[[nodiscard]] inline float magnitude4_sq(vec4 v) noexcept
{
	return dot4(v, v);
}

}
