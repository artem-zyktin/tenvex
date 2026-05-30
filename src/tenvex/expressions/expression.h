#pragma once

#include "core.h"

namespace tnvx
{

template<typename Derived>
struct Expr
{
	[[nodiscard]] TNVX_INLINE
	const Derived& self() const noexcept;
};

}

#include "expression_impl.hpp"
