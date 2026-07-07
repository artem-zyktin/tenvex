#pragma once

#include "core.h"
#include "expression.h"
#include "traits.h"
#include "concepts.h"

namespace tnvx
{

template<packed_expr E>
struct Normalize4 : Expr<Normalize4<E>>
{
	TNVX_INLINE
	explicit Normalize4(const E& TNVX_RESTRICT e) noexcept;

	[[nodiscard]] TNVX_INLINE
	vf4 eval() const noexcept;

private:
	tnvx_ref_or_value_t<E> _e;
};

template<packed_expr E> inline constexpr bool is_quat_expr<Normalize4<E>> = true;

template<packed_expr E>
Normalize4<E> normalize4(const E& e) noexcept;

}

#include "normalize4_impl.hpp"
