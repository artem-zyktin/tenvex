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
vec4 clamp(const V& v, const Lo& lo, const Hi& hi) noexcept;

template<vec_expr V>
[[nodiscard]] TNVX_INLINE
vec4 saturate(const V& v) noexcept;

template<vec_expr A, vec_expr B, scalar_expr T>
[[nodiscard]] TNVX_INLINE
vec4 lerp(const A& a, const B& b, const T& t) noexcept;

template<vec_expr A, vec_expr B>
[[nodiscard]] TNVX_INLINE
vec4 lerp(const A& a, const B& b, float t) noexcept;

template<vec_expr L, vec_expr R>
[[nodiscard]] TNVX_INLINE
float distance3(const L& l, const R& r) noexcept;

template<vec_expr L, vec_expr R>
[[nodiscard]] TNVX_INLINE
float distance3_sq(const L& l, const R& r) noexcept;

template<vec_expr V, vec_expr N>
[[nodiscard]] TNVX_INLINE
vec4 reflect(const V& v, const N& n) noexcept;

[[nodiscard]] TNVX_INLINE
vec4 orthogonal(const vec4& v);

}

#include "vec_operations_impl.hpp"
