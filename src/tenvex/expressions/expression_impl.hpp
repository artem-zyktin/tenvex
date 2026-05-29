#include "defines.h"
#include "expression.h"

namespace tnvx
{

template<typename Derived>
TNVX_INLINE
const Derived& Expr<Derived>::self() const noexcept
{
	return static_cast<const Derived&>(*this);
}

}
