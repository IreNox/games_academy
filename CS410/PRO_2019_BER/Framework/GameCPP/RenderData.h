#pragma once

#include "EntitySystem.h"

#include <framework.h>

namespace GA
{
	struct RenderDataComponent : EntityComponent
	{
		static constexpr ComponentTypeId TypeId = 0x5a98e90u;
		static EntityComponent* createState( const void* pInitData )
		{
			return new RenderDataComponent();
		}

		float				x;
		float				y;
		float				width;
		float				height;
		ga_graphics_color	color;
	};
}