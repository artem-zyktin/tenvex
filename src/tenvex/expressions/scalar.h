#pragma once

#include "core.h"
#include "expression.h"
#include "traits.h"
#include "concepts.h"

namespace tnvx
{

struct Scalar : Expr<Scalar>
{
	TNVX_INLINE
	explicit Scalar(float value) noexcept;

	[[nodiscard]] TNVX_INLINE
	vf4 eval() const noexcept;

private:
	vf4 _value;
};

template<>
inline constexpr bool is_scalar_expr<Scalar> = true;

}

#include "scalar_impl.hpp"
