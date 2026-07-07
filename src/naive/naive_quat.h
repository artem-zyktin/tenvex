#pragma once

#include "naive_vec4.h"

#include <cmath>

namespace naive
{

struct quat;

quat normalize4(quat q) noexcept;

struct quat
{
	quat() noexcept = default;

	quat(float x, float y, float z, float w) noexcept
		: _x(x), _y(y), _z(z), _w(w)
	{
	}

	[[nodiscard]] float x() const noexcept { return _x; }
	[[nodiscard]] float y() const noexcept { return _y; }
	[[nodiscard]] float z() const noexcept { return _z; }
	[[nodiscard]] float w() const noexcept { return _w; }

	[[nodiscard]] static quat identity() noexcept
	{
		return { 0.0f, 0.0f, 0.0f, 1.0f };
	}

	[[nodiscard]] static quat from_axis_angle(float ax, float ay, float az, float angle) noexcept
	{
		const float half = angle * 0.5f;
		const float c = std::cos(half);
		float s = std::sin(half);

		const float len = std::sqrt(ax * ax + ay * ay + az * az);
		const float inv = len > 0.0f ? 1.0f / len : 0.0f;
		s *= inv;

		return { ax * s, ay * s, az * s, c };
	}

	[[nodiscard]] static quat from_axis_angle(vec4 axis, float angle) noexcept
	{
		return from_axis_angle(axis.x(), axis.y(), axis.z(), angle);
	}

	[[nodiscard]] static quat from_to_rotation(vec4 from, vec4 to) noexcept
	{
		const vec4 f = normalize3(from);
		const vec4 t = normalize3(to);

		const float d = dot3(f, t);

		if (d < -0.999999f)
		{
			const float ox = std::fabs(f.x()) > std::fabs(f.z()) ? -f.y() : 0.0f;
			const float oy = std::fabs(f.x()) > std::fabs(f.z()) ? f.x() : -f.z();
			const float oz = std::fabs(f.x()) > std::fabs(f.z()) ? 0.0f : f.y();
			const float ol = std::sqrt(ox * ox + oy * oy + oz * oz);
			const float oi = ol > 0.0f ? 1.0f / ol : 0.0f;
			return { ox * oi, oy * oi, oz * oi, 0.0f };
		}

		const vec4 c = cross3(f, t);
		const float w = 1.0f + d;
		return normalize4(quat { c.x(), c.y(), c.z(), w });
	}

private:
	float _x, _y, _z, _w;
};

[[nodiscard]] inline quat operator+(quat a, quat b) noexcept
{
	return { a.x() + b.x(), a.y() + b.y(), a.z() + b.z(), a.w() + b.w() };
}

[[nodiscard]] inline quat operator-(quat a, quat b) noexcept
{
	return { a.x() - b.x(), a.y() - b.y(), a.z() - b.z(), a.w() - b.w() };
}

[[nodiscard]] inline quat operator*(quat q, float s) noexcept
{
	return { q.x() * s, q.y() * s, q.z() * s, q.w() * s };
}

[[nodiscard]] inline quat operator*(float s, quat q) noexcept
{
	return q * s;
}

[[nodiscard]] inline quat conjugate(quat q) noexcept
{
	return { -q.x(), -q.y(), -q.z(), q.w() };
}

[[nodiscard]] inline quat operator*(quat a, quat b) noexcept   // Hamilton
{
	return {
		a.w() * b.x() + a.x() * b.w() + a.y() * b.z() - a.z() * b.y(),  // x
		a.w() * b.y() - a.x() * b.z() + a.y() * b.w() + a.z() * b.x(),  // y
		a.w() * b.z() + a.x() * b.y() - a.y() * b.x() + a.z() * b.w(),  // z
		a.w() * b.w() - a.x() * b.x() - a.y() * b.y() - a.z() * b.z()   // w
	};
}

[[nodiscard]] inline quat operator*(quat q, vec4 v) noexcept   // q * (v as pure quaternion, w = 0)
{
	return q * quat { v.x(), v.y(), v.z(), 0.0f };
}

inline bool operator==(quat a, quat b) noexcept
{
	return a.x() == b.x() && a.y() == b.y()
		&& a.z() == b.z() && a.w() == b.w();
}

inline bool approx_eq(quat a, quat b, float eps = 1e-6f) noexcept
{
	return std::fabs(a.x() - b.x()) <= eps
		&& std::fabs(a.y() - b.y()) <= eps
		&& std::fabs(a.z() - b.z()) <= eps
		&& std::fabs(a.w() - b.w()) <= eps;
}

[[nodiscard]] inline vec4 rotate(vec4 v, quat q) noexcept
{
	const quat r = (q * v) * conjugate(q);
	return { r.x(), r.y(), r.z(), 0.0f };
}

[[nodiscard]] inline float dot4(quat a, quat b) noexcept
{
	return a.x() * b.x() + a.y() * b.y() + a.z() * b.z() + a.w() * b.w();
}

[[nodiscard]] inline float magnitude4(quat q) noexcept
{
	return std::sqrt(dot4(q, q));
}

[[nodiscard]] inline float magnitude4_sq(quat q) noexcept
{
	return dot4(q, q);
}

[[nodiscard]] inline quat inverse(quat q) noexcept
{
	float d = magnitude4_sq(q);
	quat c = conjugate(q);
	return { c.x() / d, c.y() / d, c.z() / d, c.w() / d };
}

[[nodiscard]] inline quat normalize4(quat q) noexcept
{
	float len = magnitude4(q);
	return { q.x() / len, q.y() / len, q.z() / len, q.w() / len };
}

[[nodiscard]] inline quat slerp(quat a, quat b, float t) noexcept
{
	float d = dot4(a, b);
	float s = 1.0f;
	if (d < 0.0f) { d = -d; s = -1.0f; }
	if (d > 0.9995f)
	{
		quat r = { a.x() * (1 - t) + b.x() * s * t, a.y() * (1 - t) + b.y() * s * t, a.z() * (1 - t) + b.z() * s * t, a.w() * (1 - t) + b.w() * s * t };
		return normalize4(r);
	}
	float theta = std::acos(d);
	float inv_sin = 1.0f / std::sin(theta);
	float wa = std::sin((1.0f - t) * theta) * inv_sin;
	float wb = std::sin(t * theta) * inv_sin * s;
	return { a.x() * wa + b.x() * wb, a.y() * wa + b.y() * wb, a.z() * wa + b.z() * wb, a.w() * wa + b.w() * wb };
}

[[nodiscard]] inline quat nlerp(quat a, quat b, float t) noexcept
{
	float s = dot4(a, b) < 0.0f ? -1.0f : 1.0f;
	quat r = { a.x() * (1 - t) + b.x() * s * t, a.y() * (1 - t) + b.y() * s * t, a.z() * (1 - t) + b.z() * s * t, a.w() * (1 - t) + b.w() * s * t };
	return normalize4(r);
}

}