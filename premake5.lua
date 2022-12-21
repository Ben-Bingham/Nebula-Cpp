gemstoneDirectory = "..\\\\Dependencies\\\\Gemstone"
require "Dependencies/Gemstone/Gemstone/useWorkspace"

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

	useGemstoneWorkspace("Dependencies/Gemstone/")
