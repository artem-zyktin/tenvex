# Toolchain cells

Listings in this directory are the last *reviewed* codegen snapshot per
cell. Cell directories are named `<compiler><version>-<os>-<arch>` (the version
is the compiler major, or `_MSC_VER` for MSVC; the OS is the TARGET os, not
the host), so snapshots from several platforms and compiler versions
coexist. The full version string and exact
command are recorded in the first lines of every listing.

A compiler upgrade produces a new cell directory in a dedicated commit with
no code changes; the superseded cell is removed in the same commit unless
there is a reason to keep both. Cells are generated on different machines
and may be updated independently.

| Cell | Compiler | Generated on | How |
| ---- | -------- | ------------ | --- |
| `gcc11-linux-x64`       | g++ 11.4.0 (Ubuntu)  | x86-64 Linux | `scripts/disasm.sh` |
| `gcc15-linux-x64`       | g++ 15.2.0 (Ubuntu)  | x86-64 Linux | `scripts/disasm.sh` |
| `clang21-linux-x64`     | clang 21.1.8 (Ubuntu) | x86-64 Linux | `scripts/disasm.sh` |
| `gcc14-linux-aarch64`   | g++ 14.2.0 (Debian)  | Raspberry Pi 5 | `scripts/disasm.sh` |
| `clang19-linux-aarch64` | clang 19.1.7 (Debian) | Raspberry Pi 5 | `scripts/disasm.sh` |
| `msvc1951-windows-x64`  | cl 19.51.36248       | Windows, VS x64 Native Tools prompt | `scripts/disasm.bat` |
