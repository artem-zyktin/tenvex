#pragma once

#include "vec4.h"
#include "internal/magnitude.h"
#include "internal/norm.h"

namespace tnvx
{

template<typename E>
TNVX_INLINE
vec4::vec4(const Expr<E>& expr) noexcept
	: _data(expr.eval())
{
}

template<typename E>
TNVX_INLINE
vec4& vec4::operator=(const Expr<E>& expr) noexcept
{
	_data = expr.eval();
	return *this;
}

TNVX_INLINE
vec4::vec4(float x, float y, float z, float w) noexcept
{
	_data = _mm_set_ps(w, z, y, x);
}

TNVX_INLINE
__m128 vec4::eval() const noexcept
{
	return _data;
}

TNVX_INLINE
auto vec4::magnitude() const noexcept
{
	return Magnitude<vec4>(*this);
}

TNVX_INLINE
auto vec4::norm() const noexcept
{
	return Norm<vec4>(*this);
}

//TNVX_INLINE
//Magnitude<vec4> vec4::magnitude() const noexcept
//{
//	return { *this };
//}
//
//TNVX_INLINE
//Norm<vec4> vec4::norm() const noexcept
//{
//	return { *this };
//}

TNVX_INLINE
float vec4::x() const noexcept
{
	return _mm_cvtss_f32(_data);
}

TNVX_INLINE
float vec4::y() const noexcept
{
	return _mm_cvtss_f32(_mm_shuffle_ps(_data, _data, _MM_SHUFFLE(1, 1, 1, 1)));
}

TNVX_INLINE
float vec4::z() const noexcept
{
	return _mm_cvtss_f32(_mm_shuffle_ps(_data, _data, _MM_SHUFFLE(2, 2, 2, 2)));
}

TNVX_INLINE
float vec4::w() const noexcept
{
	return _mm_cvtss_f32(_mm_shuffle_ps(_data, _data, _MM_SHUFFLE(3, 3, 3, 3)));
}

TNVX_INLINE
std::array<float, 4> vec4::data() const noexcept
{
	std::array<float, 4> result;
	_mm_storeu_ps(result.data(), _data);
	return result;
}

TNVX_INLINE
bool operator==(const vec4& a, const vec4& b) noexcept
{
	return _mm_movemask_ps(_mm_cmpeq_ps(a.eval(), b.eval())) == 0xF;
}

TNVX_INLINE
bool approx_eq(const vec4& a, const vec4& b, float eps) noexcept
{
	__m128 epsilon = _mm_set1_ps(eps);
	__m128 diff = _mm_sub_ps(a.eval(), b.eval());
	__m128 abs_diff = _mm_andnot_ps(_mm_set1_ps(-0.0f), diff);
	return _mm_movemask_ps(_mm_cmplt_ps(abs_diff, epsilon)) == 0xF;
}

}
