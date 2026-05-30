#pragma once

#include "core.h"
#include "expression.h"
#include "traits.h"
#include "concepts.h"

namespace tnvx
{

template<vec_expr E>
struct Norm3 : Expr<Norm3<E>>
{
	TNVX_INLINE
	explicit Norm3(const E& TNVX_RESTRICT e) noexcept;

	[[nodiscard]] TNVX_INLINE
	vf4 eval() const noexcept;

private:
	tnvx_ref_or_value_t<E> _e;
};

template<vec_expr E>
[[nodiscard]] TNVX_INLINE
Norm3<E> norm3(const E& e) noexcept;

template<vec_expr E> inline constexpr bool is_vec_expr<Norm3<E>> = true;

}
#include "norm3_impl.hpp"
