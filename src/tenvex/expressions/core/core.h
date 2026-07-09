#pragma once

#include "config.h"

#if defined(TNVX_SSE41)
#include "core_sse.h"
#elif defined(TNVX_NEON)
#include "core_neon.h"
#endif
