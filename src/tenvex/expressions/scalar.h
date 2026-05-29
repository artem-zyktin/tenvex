#pragma once

#include "defines.h"
#include "expression.h"
#include "traits.h"
#include "concepts.h"

#include <immintrin.h>

namespace tnvx
{

struct Scalar : Expr<Scalar>
{
	TNVX_INLINE
	explicit Scalar(float value) noexcept;

	[[nodiscard]] TNVX_INLINE
	__m128 eval() const noexcept;

private:
	__m128 _value;
};

template<>
inline constexpr bool is_scalar_expr<Scalar> = true;

}

#include "scalar_impl.hpp"
