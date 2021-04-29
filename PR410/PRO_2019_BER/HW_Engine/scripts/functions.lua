
function setup_default_defines()
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
end

function import_module( name )
	local module_path = "modules/" .. name .. "/" .. name .. ".lua"
	dofile( module_path )
end