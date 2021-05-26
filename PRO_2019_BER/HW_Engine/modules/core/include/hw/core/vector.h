#pragma once

#include "hw/core/types.h"

namespace hw
{
	struct Vector
	{
		float			x;
		float			y;
		float			z;
		float			w;

		static Vector	zero;
		static Vector	one;
		static Vector	unitX;
		static Vector	unitY;
		static Vector	unitZ;
		static Vector	unitW;

		inline			Vector();
		inline explicit	Vector( float xyzw );
		inline			Vector( float x, float y, float z, float w );

		inline bool		isZero( float epsilon = DefaultEpsilon ) const;
		inline bool		isEqual( const Vector& rhs, float epsilon = DefaultEpsilon) const;
		inline bool		isNormalized( float epsilon = DefaultEpsilon ) const;

		inline float	getLength() const;
		inline float	getDistance( const Vector& rhs ) const;

		inline float	dot( const Vector& rhs ) const;
		inline Vector	cross( const Vector& rhs ) const;
		inline Vector	reflect( const Vector& rhs ) const;

		inline Vector	negate() const;
		inline Vector	normalize() const;
		inline Vector	lerp(const Vector& rhs, float factor);

		inline Vector	operator+( const Vector& rhs ) const;
		inline Vector	operator-( const Vector& rhs ) const;
		inline Vector	operator/( const Vector& rhs ) const;
		inline Vector	operator*( const Vector& rhs ) const;

		inline Vector	operator/( float rhs ) const;
		inline Vector	operator*( float rhs ) const;

		inline Vector&	operator+=(const Vector& rhs) const;
		inline Vector&	operator-=(const Vector& rhs) const;
	};
}

#include "../../../src/vector.inl"
