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

						Vector();
		explicit		Vector( float xyzw );
						Vector( float x, float y, float z, float w );

		bool			isZero( float epsilon = DefaultEpsilon ) const;
		bool			isEqual( const Vector& rhs, float epsilon = DefaultEpsilon) const;
		bool			isNormalized( float epsilon = DefaultEpsilon ) const;

		float			getLength() const;
		float			getDistance( const Vector& rhs ) const;

		float			dot( const Vector& rhs ) const;
		Vector			cross( const Vector& rhs ) const;
		Vector			reflect( const Vector& rhs ) const;

		Vector			negate() const;
		Vector			normalize() const;
		Vector			lerp(const Vector& rhs, float factor);

		Vector			operator+( const Vector& rhs ) const;
		Vector			operator-( const Vector& rhs ) const;
		Vector			operator/( const Vector& rhs ) const;
		Vector			operator*( const Vector& rhs ) const;

		Vector			operator/( float rhs ) const;
		Vector			operator*( float rhs ) const;

		Vector&			operator+=(const Vector& rhs) const;
		Vector&			operator-=(const Vector& rhs) const;
	};
}