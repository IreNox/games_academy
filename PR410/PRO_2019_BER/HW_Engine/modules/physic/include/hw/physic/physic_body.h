#pragma once

#include "hw/core/matrix.h"
#include "hw/core/vector.h"

namespace hw
{
	struct PhysicShape;

	class PhysicBody
	{
	public:

		void	create( const PhysicShape& shape, const Vector& position, float mass );
		void	destroy();

		void	applyForce( const Vector& force );

		Vector	getPosition() const;
		Matrix	getRotation() const;

	private:

		void*	m_pInternalData;
	};
}