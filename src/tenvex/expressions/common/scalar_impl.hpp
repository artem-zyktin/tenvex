#pragma once

#include "scalar.h"

namespace tnvx
{

TNVX_INLINE
Scalar::Scalar(float value) noexcept
{
	_value = detail::scalar(value);
}

TNVX_INLINE
Scalar::result_t Scalar::eval() const noexcept
{
	return _value;
}

}
