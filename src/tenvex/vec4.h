#pragma once

#include "internal/expression.h"

#include <immintrin.h>

#include <array>

namespace tnvx
{

struct alignas(16) vec4 : Expr<vec4>
{
	vec4() = default;

	inline
	vec4(float x, float y, float z, float w) noexcept;

	template<typename E>
	inline
	vec4(const Expr<E>& expr) noexcept;

	template<typename E>
	inline
	vec4& operator=(const Expr<E>& expr) noexcept;

	[[nodiscard]] inline
	__m128 eval() const noexcept;

	[[nodiscard]] inline
	auto magnitude() const noexcept;

	[[nodiscard]] inline
	auto norm() const noexcept;

	[[nodiscard]] inline
	float x() const noexcept;

	[[nodiscard]] inline
	float y() const noexcept;

	[[nodiscard]] inline
	float z() const noexcept;

	[[nodiscard]] inline
	float w() const noexcept;

	[[nodiscard]] inline
	std::array<float, 4> data() const noexcept;

private:
	__m128 _data;
};

inline
bool operator==(const vec4& a, const vec4& b) noexcept;

inline
bool approx_eq(const vec4& a, const vec4& b, float eps = 1e-3f) noexcept;

}

#include "vec4_impl.hpp"
