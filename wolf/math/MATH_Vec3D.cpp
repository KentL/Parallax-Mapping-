#include "MATH_Vec3D.h"
#include <math.h>

namespace math
{
const Vec3D Vec3D::ZERO(0.0f, 0.0f, 0.0f);
const Vec3D Vec3D::ONE(1.0f, 1.0f, 1.0f);
const Vec3D Vec3D::XAXIS(1.0f, 0.0f, 0.0f);
const Vec3D Vec3D::YAXIS(0.0f, 1.0f, 0.0f);
const Vec3D Vec3D::ZAXIS(0.0f, 0.0f, 1.0f);

//----------------------------------------------------------
// Copy constructor
//----------------------------------------------------------
Vec3D::Vec3D(const Vec3D& rhs)
{
	x = rhs.x;
	y = rhs.y;
	z = rhs.z;
}

//---------------------------------------------------------
// Performs a dot product with this vector and the vector
// specified, returning the result.
//---------------------------------------------------------
float Vec3D::DotProduct(const Vec3D& p_rVec) const
{
	return (x * p_rVec.x) + (y * p_rVec.y) + (z * p_rVec.z);
}

//---------------------------------------------------------
// Performs a cross product with this vector and the vector
// specified, returning the result.
//---------------------------------------------------------
Vec3D Vec3D::CrossProduct(const Vec3D& p_rVec) const
{
	Vec3D vRet;

	vRet.x = (y * p_rVec.z) - (z * p_rVec.y);
	vRet.y = (z * p_rVec.x) - (x * p_rVec.z);
	vRet.z = (x * p_rVec.y) - (y * p_rVec.x);

	return vRet;
}

//---------------------------------------------------------
// Returns the length of this vector
//---------------------------------------------------------
int Vec3D::IntLength() const
{
	int length;

	length = this->IntLengthSquared();
	length = sqrtf(static_cast<float>( length ));

	return length;
}

//---------------------------------------------------------
// Returns the squared length of this vector
//---------------------------------------------------------
int Vec3D::IntLengthSquared() const
{
	int length;
	length = (((x) * (x)) + ((y) * (y) + ((z) * (z)) ));
	return length;
}

//---------------------------------------------------------
// Returns the length of this vector
//---------------------------------------------------------
float Vec3D::Length() const
{
	float length;
	length = (x * x) + (y * y ) + (z * z);
	length = sqrtf(length);
	return length;
}

//---------------------------------------------------------
// Returns the squared length of this vector
//---------------------------------------------------------
float Vec3D::LengthSquared() const
{
	float length;
	length = (x * x) + (y * y ) + (z * z);
	return length;
}

//---------------------------------------------------------
// Normalizes this vector, making it unit length
//---------------------------------------------------------
float Vec3D::Normalize()
{
	float fRealLength;
	float length = fRealLength = Length();
	if (length != float(0))			
	{
		length = float(1.0f) / length;	// length = inverse
		x *= length;				// don't turn small vectors into zero either...right?
		y *= length;
		z *= length;
	}
	
	return fRealLength;
}

//---------------------------------------------------------
// Returns Normalized vector, unit length, leaves the original
//---------------------------------------------------------
Vec3D Vec3D::Unit() const
{
	float length = Length();
	if (length != float(0))				
	{
		length = float(1.0f) / length;	// length = inverse
		return Vec3D(x * length, y * length, z * length);
	}
	return Vec3D::YAXIS;				// still a unit vector
}

//---------------------------------------------------------
// Override the - operator. For both Vec2D and Vec3D
//---------------------------------------------------------
Vec3D Vec3D::operator-(const Vec3D& p_rVec) const
{
	Vec3D vResult;
	vResult.x = x - p_rVec.x;
	vResult.y = y - p_rVec.y;
	vResult.z = z - p_rVec.z;
	return vResult;
}
	
//---------------------------------------------------------
// Override the (unary) - operator.
//---------------------------------------------------------
Vec3D Vec3D::operator-() const
{
	Vec3D vResult;
	vResult.x = -x;
	vResult.y = -y;
	vResult.z = -z;
	return vResult;
}

//---------------------------------------------------------
// Override the (unary) - operator.
//---------------------------------------------------------
Vec3D Vec3D::operator*(const float p_scalar) const
{
	Vec3D vResult;
	vResult.x = x * p_scalar;
	vResult.y = y * p_scalar;
	vResult.z = z * p_scalar;
	return vResult;
}

//---------------------------------------------------------
// Override the (unary) - operator.
//---------------------------------------------------------
Vec3D Vec3D::operator/(const float p_scalar) const
{
	Vec3D vResult;
	float inv = float(1.0f) / p_scalar;
	vResult.x = x * inv;
	vResult.y = y * inv;
	vResult.z = z * inv;
	return vResult;
}

//---------------------------------------------------------
// Override the += operator.
//---------------------------------------------------------
Vec3D& Vec3D::operator+=(const Vec3D& p_rVec)
{
	x += p_rVec.x;
	y += p_rVec.y;
	z += p_rVec.z;

	return (*this);
}

//---------------------------------------------------------
// Override the -= operator.
//---------------------------------------------------------
Vec3D& Vec3D::operator-=(const Vec3D& p_rVec)
{
	x -= p_rVec.x;
	y -= p_rVec.y;
	z -= p_rVec.z;

	return (*this);
}

//---------------------------------------------------------
// Override the *= operator.
//---------------------------------------------------------
Vec3D& Vec3D::operator*=(const float p_scalar)
{
	x *= p_scalar;
	y *= p_scalar;
	z *= p_scalar;

	return (*this);
}

//---------------------------------------------------------
// Override the /= operator.
//---------------------------------------------------------
Vec3D& Vec3D::operator/=(const float p_scalar)
{
	Vec3D vResult;
	float inv = float(1.0f) / p_scalar;

	x *= inv;
	y *= inv;
	z *= inv;

	return (*this);
}

}

