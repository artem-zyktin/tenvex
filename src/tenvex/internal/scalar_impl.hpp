#pragma once

#include "scalar.h"

namespace tnvx
{

TNVX_INLINE
Scalar::Scalar(float value) noexcept
	: _value(value)
{
}

[[nodiscard]] TNVX_INLINE
__m128 Scalar::eval() const noexcept
{
	return _mm_set1_ps(_value);
}

[[nodiscard]] TNVX_INLINE
float Scalar::operator[](size_t) const noexcept
{
	return _value;
}

}
