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
vf4 Scalar::eval() const noexcept
{
	return _value;
}

}
