#pragma once

#include "EntitySystem.h"

namespace GA
{
	struct PlayerComponent : EntityComponent
	{
		static constexpr ComponentTypeId TypeId = 0x6bdd19eau;
	};
}