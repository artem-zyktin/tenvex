#pragma once

#include "operations.h"

namespace tnvx
{

template<vec_expr V, vec_expr Lo, vec_expr Hi>
TNVX_INLINE
vec4 clamp(const V& v, const Lo& lo, const Hi& hi) noexcept
{
	return min(max(v, lo), hi);
}

template<vec_expr V>
TNVX_INLINE
vec4 saturate(const V& v) noexcept
{
	return clamp(v, vec4{ 0.f,0.f,0.f,0.f }, vec4{ 1.f,1.f,1.f,1.f });
}

template<vec_expr A, vec_expr B, scalar_expr T>
TNVX_INLINE
vec4 lerp(const A& a, const B& b, const T& t) noexcept
{
	return a + (b - a) * t;
}

template<vec_expr A, vec_expr B>
TNVX_INLINE
vec4 lerp(const A& a, const B& b, float t) noexcept
{
	return a + (b - a) * t;
}

template<vec_expr L, vec_expr R>
TNVX_INLINE
float dist3(const L& l, const R& r) noexcept
{
	return magnitude3(l - r);
}

template<vec_expr L, vec_expr R>
TNVX_INLINE
float dist3_sq(const L& l, const R& r) noexcept
{
	return magnitude3_sq(l - r);
}

template<vec_expr V, vec_expr N>
TNVX_INLINE
vec4 reflect(const V& v, const N& n) noexcept
{
	return v - n * (dot3(v, n) * 2.0f);
}

}
