#pragma once

#include "traits.h"
#include "expression.h"

#include <concepts>

namespace tnvx
{

template<typename T>
concept expression = requires (T t)
{
	{ t.eval() } -> std::same_as<vf4>;
	{ t.self() } -> std::same_as<const T&>;
}
&& std::is_base_of_v<Expr<T>, T>;

template<typename T>
concept vec_expr = expression<T> && is_vec_expr<T>;

template<typename T>
concept scalar_expr = expression<T> && is_scalar_expr<T>;

template<typename T>
concept quat_expr = expression<T> && is_quat_expr<T>;

template<typename L, typename R>
concept same_category = (vec_expr<L> && vec_expr<R>)
						|| (scalar_expr<L> && scalar_expr<R>)
						|| (quat_expr<L> && quat_expr<R>);

template<typename L, typename R>
concept dot4_operands = (vec_expr<L> && vec_expr<R>) || (quat_expr<L> && quat_expr<R>);

template<typename L, typename R>
concept scalable = scalar_expr<L> || scalar_expr<R>;

}
