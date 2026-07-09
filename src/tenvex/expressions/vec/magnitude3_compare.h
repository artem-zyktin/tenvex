#pragma once

#include "magnitude3.h"
#include "magnitude3_sq.h"

#include <type_traits>
#include <compare>

namespace tnvx
{

template<vec_expr A, vec_expr B>
[[nodiscard]] TNVX_INLINE
bool operator<(const Magn3<A>& a, const Magn3<B>& b) noexcept;

template<vec_expr A, typename F>
requires std::is_arithmetic_v<F>
[[nodiscard]] TNVX_INLINE
bool operator<(const Magn3<A>& a, F c) noexcept;

template<vec_expr A, typename F>
requires std::is_arithmetic_v<F>
[[nodiscard]] TNVX_INLINE
bool operator<(F c, const Magn3<A>& a) noexcept;

template<vec_expr A, vec_expr B>
[[nodiscard]] TNVX_INLINE
bool operator<=(const Magn3<A>& a, const Magn3<B>& b) noexcept;

template<vec_expr A, typename F>
requires std::is_arithmetic_v<F>
[[nodiscard]] TNVX_INLINE
bool operator<=(const Magn3<A>& a, F c) noexcept;

template<vec_expr A, typename F>
requires std::is_arithmetic_v<F>
[[nodiscard]] TNVX_INLINE
bool operator<=(F c, const Magn3<A>& a) noexcept;

template<vec_expr A, vec_expr B>
[[nodiscard]] TNVX_INLINE
bool operator>(const Magn3<A>& a, const Magn3<B>& b) noexcept;

template<vec_expr A, typename F>
requires std::is_arithmetic_v<F>
[[nodiscard]] TNVX_INLINE
bool operator>(const Magn3<A>& a, F c) noexcept;

template<vec_expr A, typename F>
requires std::is_arithmetic_v<F>
[[nodiscard]] TNVX_INLINE
bool operator>(F c, const Magn3<A>& a) noexcept;

template<vec_expr A, vec_expr B>
[[nodiscard]] TNVX_INLINE
bool operator>=(const Magn3<A>& a, const Magn3<B>& b) noexcept;

template<vec_expr A, typename F>
requires std::is_arithmetic_v<F>
[[nodiscard]] TNVX_INLINE
bool operator>=(const Magn3<A>& a, F c) noexcept;

template<vec_expr A, typename F>
requires std::is_arithmetic_v<F>
[[nodiscard]] TNVX_INLINE
bool operator>=(F c, const Magn3<A>& a) noexcept;

}

#include "magnitude3_compare_impl.hpp"
