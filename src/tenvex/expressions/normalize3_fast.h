#pragma once

#include "core.h"
#include "expression.h"
#include "traits.h"
#include "concepts.h"

namespace tnvx
{

template<packed_expr E>
struct Normalize3Fast : Expr<Normalize3Fast<E>>
{
	using result_t = vf4;

	TNVX_INLINE
	explicit Normalize3Fast(const E& TNVX_RESTRICT e) noexcept;

	[[nodiscard]] TNVX_INLINE
	result_t eval() const noexcept;

private:
	tnvx_ref_or_value_t<E> _e;
};

template<packed_expr E>
[[nodiscard]] TNVX_INLINE
Normalize3Fast<E> normalize3_fast(const E& e) noexcept;

template<vec_expr E> inline constexpr bool is_vec_expr<Normalize3Fast<E>> = true;
template<quat_expr E> inline constexpr bool is_quat_expr<Normalize3Fast<E>> = true;

}
#include "normalize3_fast_impl.hpp"
