#pragma once

#include "core.h"
#include "expression.h"
#include "traits.h"
#include "concepts.h"

namespace tnvx
{

template<vec_expr E>
struct Ceil : Expr<Ceil<E>>
{

	TNVX_INLINE
	explicit Ceil(const E& TNVX_RESTRICT e) noexcept;

	[[nodiscard]] TNVX_INLINE
	vf4 eval() const noexcept;

private:
	tnvx_ref_or_value_t<E> _e;
};

template<vec_expr E> inline constexpr bool is_vec_expr<Ceil<E>> = true;

template<vec_expr E>
[[nodiscard]] TNVX_INLINE
Ceil<E> ceil(const E& e) noexcept;

}

#include "ceil_impl.hpp"
