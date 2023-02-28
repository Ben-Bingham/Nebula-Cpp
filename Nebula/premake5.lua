require "../Dependencies/Gemstone/Gemstone/use"

project "Nebula"
	kind "ConsoleApp"
	language "C++"

	cppdialect "C++20"

	targetdir ("%{wks.location}/build/bin/%{prj.name}")
	objdir ("%{wks.location}/build/bin-int/%{prj.name}")

	filter "configurations:Debug"
		symbols "On"
		defines "NEBULA_DEBUG"
	filter {}
	
	filter "configurations:Release"
		optimize "On"
		defines "NEBULA_RELEASE"
	filter {}

	files {
		"src/**.h",
		"src/**.cpp"
	}

	includedirs {
		"src"
	}

	useGemstone("../Dependencies/Gemstone/")