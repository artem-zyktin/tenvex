#pragma once

#include "expression.h"

namespace tnvx
{

struct Scalar : Expr<Scalar>
{
	inline
	Scalar(float value) noexcept;

	[[nodiscard]] inline
	__m128 eval() const noexcept;

	[[nodiscard]] inline
	float operator[](size_t) const noexcept;

private:
	float _value;
};

}

#include "scalar_impl.hpp"
