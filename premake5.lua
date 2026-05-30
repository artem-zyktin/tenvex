workspace "tenvex"
	architecture "x64"
	configurations { "debug", "release" }
	location "build"
	startproject "tenvex_tests"

outputdir = "%{cfg.system}/x64/%{cfg.buildcfg}"

project "gtest"
	location "build"
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/output")
	objdir    ("bin/" .. outputdir .. "/intermediate")

	files {
		"thirdparty/gtest/googletest/src/gtest-all.cc",
	}

	includedirs {
		"thirdparty/gtest/googletest/include",
		"thirdparty/gtest/googletest",
	}

	filter "configurations:debug"
		runtime "Debug"
		symbols "on"
		optimize "off"

	filter "configurations:release"
		runtime "Release"
		symbols "on"
		optimize "Speed"

	filter "system:windows"
		systemversion "latest"

	filter "system:linux"
		pic "on"

	filter "system:macosx"
		pic "on"

project "benchmark"
	location "build"
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/output")
	objdir    ("bin/" .. outputdir .. "/intermediate")

	files {
		"thirdparty/benchmark/src/**.cc",
	}

	removefiles {
		"thirdparty/benchmark/src/benchmark_main.cc",
	}

	includedirs {
		"thirdparty/benchmark/include",
		"thirdparty/benchmark/src",
	}

	defines { "BENCHMARK_STATIC_DEFINE", "HAVE_STD_REGEX" }

	filter "configurations:debug"
		runtime "Debug"
		symbols "on"
		optimize "off"

	filter "configurations:release"
		runtime "Release"
		symbols "on"
		optimize "Speed"

	filter "system:windows"
		systemversion "latest"

	filter "system:linux"
		pic "on"

	filter "system:macosx"
		pic "on"

project "gtest_main"
	location "build"
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/output")
	objdir    ("bin/" .. outputdir .. "/intermediate")

	files {
		"thirdparty/gtest/googletest/src/gtest_main.cc",
	}

	includedirs {
		"thirdparty/gtest/googletest/include",
		"thirdparty/gtest/googletest",
	}

	filter "configurations:debug"
		runtime "Debug"
		symbols "on"
		optimize "off"

	filter "configurations:release"
		runtime "Release"
		symbols "on"
		optimize "Speed"

	filter "system:windows"
		systemversion "latest"

project "tenvex"
	location "build"
	kind "None"
	language "C++"
	cppdialect "C++20"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/output")
	objdir    ("bin/" .. outputdir .. "/intermediate")

	files {
		"src/tenvex/**.h",
		"src/tenvex/**.hpp",
	}

	includedirs {
		"src/tenvex",
	}

	filter "configurations:debug"
		runtime "Debug"
		symbols "on"
		optimize "off"
		defines { "TENVEX_DEBUG" }

	filter "configurations:release"
		runtime "Release"
		symbols "on"
		optimize "Speed"
		defines { "TENVEX_RELEASE" }

	filter "system:windows"
		systemversion "latest"

	filter "system:linux"
		pic "on"

	filter "system:macosx"
		pic "on"

project "tenvex_tests"
	location "build"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/output")
	objdir    ("bin/" .. outputdir .. "/intermediate")

	files {
		"src/tests/**.cpp",
	}

	includedirs {
		"src/tenvex",
		"thirdparty/gtest/googletest/include",
	}

	links { "gtest", "gtest_main" }

	filter "configurations:debug"
		runtime "Debug"
		symbols "on"
		optimize "off"
		defines { "TENVEX_DEBUG" }

	filter "configurations:release"
		runtime "Release"
		symbols "on"
		optimize "Speed"
		defines { "TENVEX_RELEASE" }

	filter "system:windows"
		systemversion "latest"

	filter "system:linux"
		pic "on"
		links { "pthread" }

	filter "system:macosx"
		pic "on"

	filter "toolset:gcc or toolset:clang"
        buildoptions { "-msse4.1" }
    filter {}

project "tenvex_bench"
	location "build"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/output")
	objdir    ("bin/" .. outputdir .. "/intermediate")

	files {
		"src/benchmarks/**.cpp",
	}

	includedirs {
		"src/tenvex",
		"thirdparty/benchmark/include",
	}

	links { "benchmark" }

	defines { "BENCHMARK_STATIC_DEFINE" }

	filter "configurations:debug"
		runtime "Debug"
		symbols "on"
		optimize "off"
		defines { "TENVEX_DEBUG" }

	filter "configurations:release"
		runtime "Release"
		symbols "on"
		optimize "Speed"
		defines { "TENVEX_RELEASE" }

	filter "system:windows"
		systemversion "latest"
		links { "Shlwapi" }

	filter "system:linux"
		pic "on"
		links { "pthread" }

	filter "system:macosx"
		pic "on"

	filter "toolset:gcc or toolset:clang"
		buildoptions { "-msse4.1" }

	filter {}
