dofile( "scripts/functions.lua" )

workspace "HW_Engine"
	configurations{ "Debug", "Release", "Master" }
	platforms{ "x64" }
	location( "build" )
	
project "HW_Engine"
	kind "WindowedApp"
	language "C++"
	
	symbols "On"
	
	if os.target() == "windows" then
		defines{ "HW_WINDOWS" }
	end
	
	filter{ "configurations:Debug" }
		defines{ "DEBUG", "HW_DEBUG" }
		
	filter{ "configurations:Release" }
		defines{ "NDEBUG", "HW_RELEASE" }
		optimize "On"

	filter{ "configurations:Master" }
		defines{ "NDEBUG", "HW_MASTER" }
		optimize "On"

	filter{}
	
	files{ "src/*.h", "src/*.cpp" }
	
	import_module( "core" )
	import_module( "resource" )
	import_module( "sound" )
	import_module( "physic" )