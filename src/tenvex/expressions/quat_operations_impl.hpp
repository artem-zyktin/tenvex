#pragma once

#include "quat_operations.h"

#include <cmath>

namespace tnvx
{

template<quat_expr A, quat_expr B>
TNVX_INLINE
quat slerp(const A& a, const B& b, float t) noexcept
{
	float d = float(dot4(a, b));
	float s = 1.0f;

	if (d < 0.0f)
	{
		d = -d;
		s = -1.0f;
	}

	if (d > 0.9995f)
	{
		return normalize(a * (1.0f - t) + b * (s * t));
	}

	const float theta = std::acos(d);
	const float inv_sin = 1.0f / std::sin(theta);
	const float wa = std::sin((1.0f - t) * theta) * inv_sin;
	const float wb = std::sin(t * theta) * inv_sin * s;

	return a * wa + b * wb;
}

}
