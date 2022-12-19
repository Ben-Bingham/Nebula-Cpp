workspace "Nebula"
	configurations { "Debug", "Release" }
	platforms "x64"

	filter "platforms:x64"
		architecture "x64"

	filter "configurations:Debug"
		symbols "On"
	filter {}

	filter "configurations:Release"
		optimize "On"
	filter {}

	startproject "Nebula"

	include "Nebula"

	group "Gemstone"
		include "Dependencies/Gemstone/Celestite"
		include "Dependencies/Gemstone/Lazuli"
		include "Dependencies/Gemstone/Malachite"
		include "Dependencies/Gemstone/Wavellite"
		include "Dependencies/Gemstone/Ruby"
		include "Dependencies/Gemstone/Pyrite"
	group ""