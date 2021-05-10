#pragma once

#include "EntitySystem.h"

namespace GA
{
	struct CollisionInitData
	{
		float		width;
		float		height;
	};

	struct CollisionComponent : EntityComponent
	{
		static constexpr ComponentTypeId TypeId = 0xa432311bu;
		static EntityComponent* createState( const void* pInitData )
		{
			CollisionComponent* pComponent = new CollisionComponent();

			if( pInitData != nullptr )
			{
				const CollisionInitData* pData = (const CollisionInitData*)pInitData;
				pComponent->width	= pData->width;
				pComponent->height	= pData->height;
			}

			return pComponent;
		}

		float		width;
		float		height;
		EntityId	collistionEntity;
	};
}