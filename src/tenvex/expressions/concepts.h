#pragma once

#include "traits.h"
#include "expression.h"

#include <concepts>

namespace tnvx
{

template<typename T>
concept expression = requires (T t)
{
	{ t.eval() } -> std::same_as<__m128>;
	{ t.self() } -> std::same_as<const T&>;
}
&& std::is_base_of_v<Expr<T>, T>;

template<typename T>
concept vec_expr = expression<T> && is_vec_expr<T>;

template<typename T>
concept scalar_expr = expression<T> && is_scalar_expr<T>;

}
