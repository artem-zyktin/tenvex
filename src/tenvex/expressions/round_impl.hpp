#pragma once

#include "round.h"

namespace tnvx
{

template<vec_expr E>
TNVX_INLINE
Round<E>::Round(const E& TNVX_RESTRICT e) noexcept
	: _e(e)
{
}

template<vec_expr E>
[[nodiscard]] TNVX_INLINE
Round<E>::result_t Round<E>::eval() const noexcept
{
	return detail::round(_e.eval());
}

template<vec_expr E>
[[nodiscard]] TNVX_INLINE
Round<E> round(const E& e) noexcept
{
	return Round<E>(e);
}

}
