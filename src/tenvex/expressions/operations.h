#pragma once

#include "add.h"
#include "sub.h"
#include "mul.h"
#include "magnitude3.h"
#include "magnitude3_sq.h"
#include "dot3.h"
#include "min.h"
#include "max.h"
#include "vec4.h"


namespace tnvx
{

template<vec_expr V, vec_expr Lo, vec_expr Hi>
[[nodiscard]] TNVX_INLINE
auto clamp(const V& v, const Lo& lo, const Hi& hi) noexcept;

template<vec_expr V>
[[nodiscard]] TNVX_INLINE
auto saturate(const V& v) noexcept;

template<vec_expr A, vec_expr B, scalar_expr T>
[[nodiscard]] TNVX_INLINE
auto lerp(const A& a, const B& b, tnvx_ref_or_value_t<T> t) noexcept;

template<vec_expr L, vec_expr R>
[[nodiscard]] TNVX_INLINE
auto dist3(const L& l, const R& r) noexcept;

template<vec_expr L, vec_expr R>
[[nodiscard]] TNVX_INLINE
auto dist3_sq(const L& l, const R& r) noexcept;

template<vec_expr V, vec_expr N>
[[nodiscard]] TNVX_INLINE
auto reflect(const V& v, const N& n) noexcept;

}

#include "operations_impl.hpp"
