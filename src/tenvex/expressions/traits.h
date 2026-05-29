#pragma once

#include <type_traits>

namespace tnvx
{

template<typename T>
inline constexpr bool is_stored_by_value_v = std::is_trivially_copyable_v<T>
											 && std::is_trivially_destructible_v<T>
											 && sizeof(T) <= 16;

template<typename T>
using tnvx_ref_or_value_t = std::conditional_t<is_stored_by_value_v<T>, T, const T&>;

template<typename>
inline constexpr bool is_scalar_expr = false;

template<typename>
inline constexpr bool is_vec_expr = false;

}
