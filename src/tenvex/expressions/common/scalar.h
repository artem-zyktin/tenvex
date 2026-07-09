#pragma once

#include "expressions/core/core.h"
#include "expressions/protocol/traits.h"
#include "expressions/protocol/concepts.h"

namespace tnvx
{

struct Scalar
{
	using result_t = vf4;

	TNVX_INLINE
	explicit Scalar(float value) noexcept;

	[[nodiscard]] TNVX_INLINE
	result_t eval() const noexcept;

private:
	vf4 _value;
};

static_assert(is_stored_by_value_v<Scalar>, "Scalar must be stored by value");

template<>
inline constexpr bool is_scalar_expr<Scalar> = true;

}

#include "scalar_impl.hpp"
