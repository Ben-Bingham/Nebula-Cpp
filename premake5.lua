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
		-- include "Dependencies/Gemstone/Malachite"
		-- include "Dependencies/Gemstone/Lazuli"
		-- include "Dependencies/Gemstone/Ruby"
		externalproject "Lazuli"
   			location "Dependencies/Gemstone/Lazuli"
  			uuid "B64347C0-A2E5-7196-8BA0-85EA77E1F8E6"
   			kind "StaticLib"

		externalproject "Malachite"
   			location "Dependencies/Gemstone/Malachite"
  			uuid "ED868CE3-59F1-405A-A22F-F2FF0ED91EAF"
   			kind "StaticLib"

		externalproject "Ruby"
   			location "Dependencies/Gemstone/Ruby"
  			uuid "67058C7C-533C-8D0D-FC28-7310E83E090F"
   			kind "StaticLib"
	group ""
