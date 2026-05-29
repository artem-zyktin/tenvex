#pragma once

#include "scalar.h"

namespace tnvx
{

TNVX_INLINE
Scalar::Scalar(float value) noexcept
{
	_value = _mm_set1_ps(value);
}

TNVX_INLINE
__m128 Scalar::eval() const noexcept
{
	return _value;
}

}
