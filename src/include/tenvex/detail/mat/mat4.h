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

	mat4(float m00, float m10, float m20, float m30,
		 float m01, float m11, float m21, float m31,
		 float m02, float m12, float m22, float m32,
		 float m03, float m13, float m23, float m33) noexcept;

	mat4(vf4 col0, vf4 col1, vf4 col2, vf4 col3) noexcept;

	mat4(vec4 col0, vec4 col1, vec4 col2, vec4 col3) noexcept;

	static mat4 zero() noexcept;
	static mat4 identity() noexcept;
	static mat4 translation(float x, float y, float z) noexcept;
	static mat4 translation(const vec4& vec) noexcept;
	static mat4 scaling(float s) noexcept;
	static mat4 scaling(float x, float y, float z) noexcept;
	static mat4 scaling(const vec4& v) noexcept;
	static mat4 from_quat(const quat& q) noexcept;
	static mat4 from_rotation(const vec4& axis, float angle) noexcept;

	const vf4& col(int j) const noexcept;
	float at(int i, int j) const noexcept;

	result_t eval() const noexcept;

private:
	mf4 _data;
};

}

#include "mat4_impl.hpp"
