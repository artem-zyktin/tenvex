#pragma once

#include "core.h"
#include "traits.h"
#include "concepts.h"

#include "quat.h"

namespace tnvx
{

template<quat_expr A, quat_expr B>
[[nodiscard]] TNVX_INLINE
quat slerp(const A& a, const B& b, float t) noexcept;

template<quat_expr A, quat_expr B>
[[nodiscard]] TNVX_INLINE
quat nlerp(const A& a, const B& b, float t) noexcept;

}

#include "quat_operations_impl.hpp"
