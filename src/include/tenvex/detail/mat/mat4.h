#pragma once

#include "tenvex/detail/core/core.h"
#include "tenvex/detail/protocol/traits.h"
#include "tenvex/detail/protocol/concepts.h"

#include "tenvex/detail/vec.h"
#include "tenvex/detail/quat.h"

namespace tnvx
{

struct alignas(64) mat4
{
	using result_t = mf4;

	mat4() noexcept = default;

	TNVX_INLINE
	mat4(float m00, float m10, float m20, float m30,
		 float m01, float m11, float m21, float m31,
		 float m02, float m12, float m22, float m32,
		 float m03, float m13, float m23, float m33) noexcept;

	template<mat_expr E>
	TNVX_INLINE
	mat4(const E& TNVX_RESTRICT e) noexcept;

	TNVX_INLINE
	mat4(vf4 col0, vf4 col1, vf4 col2, vf4 col3) noexcept;

	TNVX_INLINE
	mat4(vec4 col0, vec4 col1, vec4 col2, vec4 col3) noexcept;

	TNVX_INLINE
	explicit mat4(const mf4& data) noexcept;

	[[nodiscard]] TNVX_INLINE
	static mat4 zero() noexcept;

	[[nodiscard]] TNVX_INLINE
	static mat4 identity() noexcept;

	[[nodiscard]] TNVX_INLINE
	static mat4 translation(const vec4& vec) noexcept;

	[[nodiscard]] TNVX_INLINE
	static mat4 translation(float x, float y, float z) noexcept;

	[[nodiscard]] TNVX_INLINE
	static mat4 scaling(float s) noexcept;

	[[nodiscard]] TNVX_INLINE
	static mat4 scaling(float x, float y, float z) noexcept;

	[[nodiscard]] TNVX_INLINE
	static mat4 scaling(const vec4& v) noexcept;

	[[nodiscard]] TNVX_INLINE
	static mat4 from_quat(const quat& q) noexcept;

	[[nodiscard]] TNVX_INLINE
	static mat4 from_rotation(const vec4& axis, float angle) noexcept;

	[[nodiscard]] TNVX_INLINE
	vec4 col(int j) const noexcept;

	template<uint8_t i, uint8_t j>
	[[nodiscard]] TNVX_INLINE
	float at() const noexcept;

	[[nodiscard]] TNVX_INLINE
	result_t eval() const noexcept;

private:
	mf4 _data;
};

}

#include "mat4_impl.hpp"
