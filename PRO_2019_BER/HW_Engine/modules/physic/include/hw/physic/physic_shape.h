#pragma once

#include "hw/core/vector.h"

namespace hw
{
	enum class PhysicShapeType
	{
		Box,
		Sphere,
		Capsule,
		Mesh
	};

	union PhysicShapeData
	{
		struct {
			Vector			extends;
		} box;
		struct {
			float			radius;
		} sphere;
		struct {
			float			radius;
			float			height;
		} capsule;
		struct {
			const Vector*	pVertices;
			size_t			vertexCount;
		} mesh;
	};

	struct PhysicShape
	{
		PhysicShapeType		type;
		PhysicShapeData		data;

		void				setBox( const Vector& exdends );
		void				setSphere( float radius );
		void				setCapsule( float radius, float height );
		void				setMesh( const Vector* pVertices, size_t vertexCount );
	};
}