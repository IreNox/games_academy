dofile( "scripts/functions.lua" )

workspace( "HW_Engine" )
	configurations{ "Debug", "Release", "Master" }
	platforms{ "x64" }
	location( "build" )
	systemversion( "latest" )
	
project( "HW_Engine" )
	kind( "WindowedApp" )
	language( "C++" )
	
	setup_default_defines()
	
	files{ "src/engine/*.h", "src/engine/*.cpp" }
	
	import_module( "core" )
	import_module( "resource" )
	import_module( "sound" )
	import_module( "physic" )
	
project( "HW_Converter" )
	kind( "ConsoleApp" )
	language( "C++" )
	
	setup_default_defines()
	
	files{ "src/converter/*.h", "src/converter/*.cpp" }
	
	import_module( "core" )
	import_module( "resource" )
	import_module( "resource_tools" )
