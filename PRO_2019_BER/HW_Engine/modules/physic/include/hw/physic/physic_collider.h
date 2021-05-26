#pragma once

namespace hw
{
	struct PhysicShape;
	struct Vector;

	class PhysicCollider
	{
	public:

		void	create( const PhysicShape& shape, const Vector& position );
		void	destroy();

	private:

		void*	m_pInternalData;
	};
}