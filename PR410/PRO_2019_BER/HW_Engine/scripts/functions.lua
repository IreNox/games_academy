
function import_module( name )
	local module_path = "modules/" .. name .. "/" .. name .. ".lua"
	dofile( module_path )
end