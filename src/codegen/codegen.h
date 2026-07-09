#pragma once

// Codegen probes: compile-only TUs for inspecting the generated assembly.
// Never linked into anything. See docs/decisions.md ("Committed codegen
// listings") and scripts/disasm.sh / disasm.bat.
//
// TNVX_CODEGEN = extern "C" (stable, demangled, cross-toolchain symbol
// names) + noinline (the probe survives as a unit of analysis).

#include "tenvex.h"

#include <cstddef>

#if defined(_MSC_VER)
	#define TNVX_CODEGEN extern "C" __declspec(noinline)
#else
	#define TNVX_CODEGEN extern "C" __attribute__((noinline, used))
#endif

using namespace tnvx;
