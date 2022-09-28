workspace "Nebula"
	configurations {"Debug", "Release"}
	platforms {"x64"}

	startproject "Nebula"

	filter "platforms:x64"
		architecture "x64"

	filter "configurations:Debug"
		defines {
			"MALACHITE_DEBUG",
			"LAZULI_DEBUG",
			"RUBY_DEBUG",
			"GLEW_STATIC"
		}
		symbols "On"
		
	filter "configurations:Release"
		defines { 
			"MALACHITE_RELEASE",
			"LAZULI_RELEASE",
			"RUBY_RELEASE",
			"GLEW_STATIC"
		}
		optimize "On"
	filter {}

	include "Nebula"
	
	group "Gemstone"
		include "Dependencies/Gemstone/Malachite"
		include "Dependencies/Gemstone/Lazuli"
		include "Dependencies/Gemstone/Ruby"
	group ""
