#pragma once

namespace hw
{
	class PhysicBody;
	class PhysicCollider;
	struct PhysicShape;
	struct Vector;

	class PhysicSystem
	{
	public:

				PhysicSystem();
				~PhysicSystem();

		void	create( const Vector& gravity );
		void	destroy();

		void	update();

		void	addBody( const PhysicBody* pBody );
		void	removeBody( const PhysicBody* pBody );
		void	addCollider( const PhysicCollider* pCollider );
		void	removeCollider( const PhysicCollider* pCollider );

		bool	checkCollision( const PhysicShape& shape, const Vector& position ) const;
		bool	checkCollision( const PhysicBody& body, const PhysicCollider& collider ) const;

	private:

		void*	m_pInternalData;
	};
}