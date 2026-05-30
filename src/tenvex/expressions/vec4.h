#pragma once

#include "core.h"
#include "expression.h"
#include "traits.h"
#include "concepts.h"

namespace tnvx
{

struct alignas(16) vec4 : Expr<vec4>
{
	TNVX_INLINE
	vec4() noexcept = default;

	TNVX_INLINE
	vec4(float x, float y, float z, float w = 0) noexcept;

	template<vec_expr E>
	TNVX_INLINE
	vec4(const E& TNVX_RESTRICT e) noexcept;

	[[nodiscard]] TNVX_INLINE
	vf4 eval() const noexcept;

private:
	vf4 _data;
};

template<> inline constexpr bool is_vec_expr<vec4> = true;

TNVX_INLINE
bool approx_eq(const vec4& lhs, const vec4& rhs, float eps = 1e-6f) noexcept;

TNVX_INLINE
bool operator==(const vec4& lhs, const vec4& rhs) noexcept;

}

#include "vec4_impl.hpp"
