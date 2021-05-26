
function setup_default_defines()
	symbols "On"
	
	if os.target() == "windows" then
		defines{ "HW_WINDOWS", "_CRT_SECURE_NO_WARNINGS" }
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
end

function import_module( name )
	local module_path = "modules/" .. name .. "/" .. name .. ".lua"
	dofile( module_path )
end

function import_third_party( name )
	local module_path = "third_party/" .. name .. "/" .. name .. ".lua"
	dofile( module_path )
end