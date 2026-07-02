#pragma once

namespace naive
{

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

}