workspace "tenvex"
	architecture "x64"
	configurations { "debug", "release" }
	location "build"

outputdir = "%{cfg.system}/x64/%{cfg.buildcfg}"

project "tenvex"
	location "build"
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/output")
	objdir    ("bin/" .. outputdir .. "/intermediate")

	files {
		"src/tenvex/**.h",
		"src/tenvex/**.hpp",
		"src/tenvex/**.cpp",
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
