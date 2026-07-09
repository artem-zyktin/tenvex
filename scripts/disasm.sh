#!/usr/bin/env bash
#
# Generate reference assembly listings for the codegen probes
# (src/codegen/cg_*.cpp) into asm/<compiler><major>-<os>-<arch>/, one .s
# per probe TU (e.g. asm/gcc13-linux-x64, asm/clang18-macos-arm64). The OS
# component is the TARGET os, not the host. Versioned cell names let
# snapshots from several platforms and compiler versions coexist.
# The first lines of every listing record the full compiler version and the
# exact command. See docs/decisions.md ("Committed codegen listings").
#
# On an x86-64 host: native gcc/clang cells + cross aarch64 cells.
# On an AArch64 host (e.g. Raspberry Pi): native gcc/clang aarch64 cells.
# Missing toolchains are skipped with a note.
#
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
ROOT="$(cd "$SCRIPT_DIR/.." && pwd)"
SRC="$ROOT/src/codegen"
COMMON=(-S -O3 -std=c++20 -Wall "-I$ROOT/src/tenvex")

emit_cell() {
	local name="$1"; shift    # compiler family: gcc / clang
	local os="$1"; shift      # target os: linux / macos
	local arch="$1"; shift    # target arch: x64 / aarch64 / arm64
	local cxx="$1"; shift
	local extra=("$@")

	if ! command -v "$cxx" >/dev/null 2>&1; then
		echo "skip  ${name}-${os}-${arch} ($cxx not found)"
		return
	fi

	local major cell out ver
	major="$("$cxx" -dumpversion | cut -d. -f1)"
	cell="${name}${major}-${os}-${arch}"
	out="$ROOT/asm/$cell"
	mkdir -p "$out"
	ver="$("$cxx" --version | head -1)"

	local f base ok=1
	for f in "$SRC"/cg_*.cpp; do
		base="$(basename "$f" .cpp)"
		if "$cxx" "${COMMON[@]}" "${extra[@]}" -o "$out/$base.s.tmp" "$f" 2>"$out/$base.err"; then
			{
				echo "# $ver"
				echo "# $cxx ${COMMON[*]} ${extra[*]} $(basename "$f")" | sed "s|$ROOT/||g"
				cat "$out/$base.s.tmp"
			} >"$out/$base.s"
			rm -f "$out/$base.s.tmp" "$out/$base.err"
		else
			echo "FAIL  $cell/$base (see asm/$cell/$base.err)"
			rm -f "$out/$base.s.tmp"
			ok=0
		fi
	done
	[ "$ok" = 1 ] && echo "done  $cell ($ver)"
}

HOST_ARCH="$(uname -m)"
case "$(uname -s)" in
	Darwin) HOST_OS=macos ;;
	*)      HOST_OS=linux ;;
esac

if [ "$HOST_ARCH" = "x86_64" ]; then
	emit_cell gcc   "$HOST_OS" x64 g++     -msse4.1 -masm=intel
	emit_cell clang "$HOST_OS" x64 clang++ -msse4.1 -masm=intel
	# cross cells target linux regardless of host
	emit_cell gcc   linux aarch64 aarch64-linux-gnu-g++
	emit_cell clang linux aarch64 clang++ --target=aarch64-linux-gnu
elif [ "$HOST_ARCH" = "aarch64" ] || [ "$HOST_ARCH" = "arm64" ]; then
	if [ "$HOST_OS" = "macos" ]; then
		emit_cell clang macos arm64 clang++
	else
		emit_cell gcc   linux aarch64 g++
		emit_cell clang linux aarch64 clang++
	fi
else
	echo "error: unsupported host arch '$HOST_ARCH'" >&2
	exit 1
fi
