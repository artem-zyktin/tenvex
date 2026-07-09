#pragma once

#include "core.h"
#include "traits.h"
#include "concepts.h"

namespace tnvx
{

template<vec_expr E>
struct Frac
{
	using result_t = vf4;

	TNVX_INLINE
	explicit Frac(const E& TNVX_RESTRICT e) noexcept;

	[[nodiscard]] TNVX_INLINE
	result_t eval() const noexcept;

private:
	tnvx_ref_or_value_t<E> _e;
};

template<vec_expr E> inline constexpr bool is_vec_expr<Frac<E>> = true;

template<vec_expr E>
[[nodiscard]] TNVX_INLINE
Frac<E> frac(const E& e) noexcept;

}

#include "frac_impl.hpp"
