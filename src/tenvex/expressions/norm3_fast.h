#pragma once

#include "core.h"
#include "expression.h"
#include "traits.h"
#include "concepts.h"

namespace tnvx
{

template<vec_expr E>
struct Norm3Fast : Expr<Norm3Fast<E>>
{
	TNVX_INLINE
	explicit Norm3Fast(const E& TNVX_RESTRICT e) noexcept;

	[[nodiscard]] TNVX_INLINE
	vf4 eval() const noexcept;

private:
	tnvx_ref_or_value_t<E> _e;
};

template<vec_expr E>
[[nodiscard]] TNVX_INLINE
Norm3Fast<E> norm3_fast(const E& e) noexcept;

template<vec_expr E> inline constexpr bool is_vec_expr<Norm3Fast<E>> = true;

}
#include "norm3_fast_impl.hpp"
