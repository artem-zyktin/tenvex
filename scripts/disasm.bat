@echo off
setlocal enabledelayedexpansion
rem
rem Generate reference assembly listings for the codegen probes
rem (src\codegen\cg_*.cpp) into asm\msvc<_MSC_VER>-windows-<arch>\, one .asm
rem per probe TU (e.g. asm\msvc1944-windows-x64). Versioned cell names let snapshots
rem from several platforms and compiler versions coexist.
rem Run from an "x64 Native Tools Command Prompt for VS" (cl must be in PATH).
rem See docs\decisions.md ("Committed codegen listings").
rem

where cl >nul 2>nul
if errorlevel 1 (
	echo error: cl not found - run from an x64 Native Tools command prompt
	exit /b 1
)

set "ROOT=%~dp0.."
set "TMPDIR=%TEMP%\tenvex_disasm"
if not exist "%TMPDIR%" mkdir "%TMPDIR%"

rem _MSC_VER via the preprocessor - locale-independent, exact
echo _MSC_VER> "%TMPDIR%\ver.c"
set "MSCVER="
for /f %%v in ('cl /nologo /EP "%TMPDIR%\ver.c" 2^>nul') do set "MSCVER=%%v"
if not defined MSCVER (
	echo error: could not determine _MSC_VER
	exit /b 1
)

rem target arch from the environment set up by vcvars
set "ARCH=%VSCMD_ARG_TGT_ARCH%"
if not defined ARCH set "ARCH=x64"

set "CELL=msvc%MSCVER%-windows-%ARCH%"
set "OUT=%ROOT%\asm\%CELL%"
if not exist "%OUT%" mkdir "%OUT%"

set "CLVER="
for /f "delims=" %%v in ('cl 2^>^&1 ^| findstr /r /c:"[0-9][0-9]*\.[0-9]"') do if not defined CLVER set "CLVER=%%v"

set "FLAGS=/nologo /c /O2 /std:c++20 /EHsc /W3 /I"%ROOT%\src\tenvex""
set "FLAGSPRINT=/nologo /c /O2 /std:c++20 /EHsc /W3 /Isrc\tenvex"

for %%f in ("%ROOT%\src\codegen\cg_*.cpp") do (
	cl %FLAGS% /FA /Fa"%TMPDIR%\%%~nf.asm" /Fo"%TMPDIR%\%%~nf.obj" "%%f" >nul
	if errorlevel 1 (
		echo FAIL  %CELL%/%%~nf
	) else (
		> "%OUT%\%%~nf.asm" (
			echo ; !CLVER!
			echo ; cl %FLAGSPRINT% /FA %%~nxf
			type "%TMPDIR%\%%~nf.asm"
		)
		echo done  %CELL%/%%~nf
	)
)

rmdir /s /q "%TMPDIR%" 2>nul
endlocal
