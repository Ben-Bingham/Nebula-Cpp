workspace "Nebula"
	configurations { "Debug", "Release" }
	platforms "x64"

	-- defines "GEM_ASSETS_STRING=\"..\\\\Dependencies\\\\Gemstone\\\\Gemstone\\\\assets\\\\ \""

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
	include "Dependencies/Gemstone/Gemstone"
	include "Dependencies/Gemstone/vendor/ImGui"