#!/usr/bin/env bash
#
# Generate gmake2 (Makefile) project files for Linux ARM64.
# Analogous to config-vs2026.bat, but for the native aarch64 toolchain (Raspberry Pi).
#
set -euo pipefail

# Resolve the project root relative to this script (assumes it lives in scripts/).
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
ROOT_DIR="$(cd "$SCRIPT_DIR/.." && pwd)"
cd "$ROOT_DIR"

PREMAKE="$ROOT_DIR/premake/bin/linux/arm64/premake5"

if [[ ! -f "$PREMAKE" ]]; then
	echo "error: premake5 not found at $PREMAKE" >&2
	exit 1
fi

# A binary moved through a zip often loses its executable bit — restore it.
chmod +x "$PREMAKE"

"$PREMAKE" gmake2
