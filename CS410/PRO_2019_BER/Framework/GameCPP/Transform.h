#pragma once

#include "EntitySystem.h"

namespace GA
{
	struct TransformInitData
	{
		float x;
		float y;
	};

	struct TransformComponent : EntityComponent
	{
		static constexpr ComponentTypeId TypeId = 0xf543030eu;
		static EntityComponent* createState( const void* pInitData )
		{
			TransformComponent* pComponent = new TransformComponent();

			if( pInitData != nullptr )
			{
				const TransformInitData* pData = (const TransformInitData*)pInitData;
				pComponent->x = pData->x;
				pComponent->y = pData->y;
			}

			return pComponent;
		}

		float x = 0.0f;
		float y = 0.0f;
	};
}
