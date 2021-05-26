#pragma once

#include "hw/core/vector.h"

namespace hw
{
	struct Matrix
	{
		Vector			x;
		Vector			y;
		Vector			z;
		Vector			w;

		static Matrix	zero;
		static Matrix	identity;

						Matrix();

		static Matrix	createRotationX( float x );
		static Matrix	createRotationY( float y );
		static Matrix	createRotationZ( float z );
		static Matrix	createScale( const Vector& scale );
		static Matrix	createTranslation( const Vector& position );

		bool			isZero( float epsilon = DefaultEpsilon ) const;
		bool			isIdentity( float epsilon = DefaultEpsilon ) const;
		bool			isEqual( const Matrix& rhs, float epsilon = DefaultEpsilon ) const;

		Matrix			tryInvert() const;
		Matrix			transpose() const;
		Matrix			lerp(const Matrix& rhs, float factor) const;

		Vector			transform( const Vector& v ) const;

		Matrix			operator*( const Matrix& rhs );
		Matrix&			operator*=(const Matrix& rhs);
	};
}