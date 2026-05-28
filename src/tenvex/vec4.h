#pragma once

#include "internal/expression.h"

#include <immintrin.h>

namespace tnvx
{

struct alignas(16) vec4 : public Expr<vec4>
{
	vec4() = default;

	vec4(float x, float y, float z, float w);

	template<typename E>
	vec4(const Expr<E>& expr);

	template<typename E>
	vec4& operator=(const Expr<E>& expr);

	__m128 eval() const noexcept;

	float magnitude() const noexcept;
	vec4 norm() const noexcept;

	float x() const noexcept;
	float y() const noexcept;
	float z() const noexcept;
	float w() const noexcept;

private:
	__m128 _data;
};

} // namespace tenvex
