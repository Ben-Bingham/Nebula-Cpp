require "../Dependencies/Gemstone/Gemstone/use"

project "Nebula"
	kind "ConsoleApp"
	language "C++"

	cppdialect "C++20"

	targetdir ("%{wks.location}/build/bin/%{prj.name}")
	objdir ("%{wks.location}/build/bin-int/%{prj.name}")

	files {
		"src/**.h",
		"src/**.cpp"
	}

	includedirs {
		"src"
	}

	print "------------------------------ Nebula Using Gemstone ------------------------------"
	useGemstone("../Dependencies/Gemstone")
	print "------------------------------ Nebula Done Using Gemstone ------------------------------"
