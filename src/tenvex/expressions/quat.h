#pragma once

#include "core.h"
#include "traits.h"
#include "concepts.h"

#include "vec4.h"

namespace tnvx
{

struct alignas(16) quat
{
	using result_t = vf4;

	TNVX_INLINE
	quat() noexcept = default;

	TNVX_INLINE
	quat(float x, float y, float z, float w) noexcept;

	template<quat_expr E>
	TNVX_INLINE
	quat(const E& e) noexcept;

	[[nodiscard]] TNVX_INLINE
	result_t eval() const noexcept;

	[[nodiscard]] TNVX_INLINE
	float x() const noexcept;

	[[nodiscard]] TNVX_INLINE
	float y() const noexcept;

	[[nodiscard]] TNVX_INLINE
	float z() const noexcept;

	[[nodiscard]] TNVX_INLINE
	float w() const noexcept;

	[[nodiscard]] TNVX_INLINE static quat identity() noexcept;
	[[nodiscard]] TNVX_INLINE static quat from_axis_angle(float ax, float ay, float az, float angle) noexcept;
	[[nodiscard]] TNVX_INLINE static quat from_axis_angle(vec4 axis, float angle) noexcept;
	[[nodiscard]] TNVX_INLINE static quat from_to_rotation(vec4 from, vec4 to) noexcept;

private:
	vf4 _data;
};

template<> inline constexpr bool is_quat_expr<quat> = true;

TNVX_INLINE
bool approx_eq(const quat& lhs, const quat& rhs, float eps = 1e-6f) noexcept;

TNVX_INLINE
bool operator==(const quat& lhs, const quat& rhs) noexcept;

}

#include "quat_impl.hpp"
