#pragma once

#include "defines.h"

#include <immintrin.h>
#include <cstdint>
#include <concepts>

namespace tnvx
{

template<typename Derived>
struct Expr
{
	[[nodiscard]] inline
	const Derived& self() const noexcept;

	[[nodiscard]] inline
	__m128 eval() const noexcept;

	[[nodiscard]] inline
	float operator[](size_t i) const noexcept;
};

template<typename T>
concept expression = requires(T a)
{
	{ a.eval() } -> std::same_as<__m128>;
}
&& std::derived_from<T, Expr<T>>;

class Scalar;

template<typename T>
concept vector_expression = expression<T> && !std::same_as<T, Scalar>;

template<typename T>
constexpr bool tnvx_store_by_value = std::is_trivially_copyable_v<T>
									 && std::is_trivially_destructible_v<T>
									 && sizeof(T) <= 16;

template<typename T>
using tnvx_type_storage = std::conditional_t<tnvx_store_by_value<T>, T, const T&>;

} // namespace tnvx

#include "expression_impl.hpp"
