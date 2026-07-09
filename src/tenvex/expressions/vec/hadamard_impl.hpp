#pragma once

#include "hadamard.h"

namespace tnvx
{

template<vec_expr L, vec_expr R>
TNVX_INLINE
Hadamard<L, R>::Hadamard(const L& TNVX_RESTRICT l, const R& TNVX_RESTRICT r) noexcept
	: _l(l), _r(r)
{
}

template<vec_expr L, vec_expr R>
TNVX_INLINE
Hadamard<L, R>::result_t Hadamard<L, R>::eval() const noexcept
{
	return detail::mul(_l.eval(), _r.eval());
}

template<vec_expr L, vec_expr R>
TNVX_INLINE
Hadamard<L, R> hadamard(const L& l, const R& r) noexcept
{
	return { l, r };
}

}
