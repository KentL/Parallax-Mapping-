#ifndef MATH_VECTOR3D_H
#define MATH_VECTOR3D_H

namespace math
{
class Vec3D
{
	public:
		//---------------------------------------------------------------------
		// PUBLIC INTERFACE
		//---------------------------------------------------------------------
		Vec3D() : x(0.0f), y(0.0f), z(0.0f){}
		Vec3D( float p_x, float p_y, float p_z ) : x(p_x), y(p_y), z(p_z) {}
		Vec3D(const Vec3D& rhs);
		Vec3D& operator=(const Vec3D& rhs);
		
		void Set(float p_x, float p_y, float p_z)
		{
			x = p_x;
			y = p_y;
			z = p_z;
		}
		
		void Set(Vec3D p_v)
		{
			x = p_v.x;
			y = p_v.y;
			z = p_v.z;
		}
		
		float DotProduct( const Vec3D& p_rVec ) const;
		Vec3D CrossProduct( const Vec3D& p_rVec ) const;
		int IntLength() const;
		int IntLengthSquared() const;
		float Length() const;
		float LengthSquared() const;
		float Normalize();
		Vec3D Unit() const;

		Vec3D operator + (const Vec3D& p_rVec) const;
		Vec3D operator - (const Vec3D& p_rVec) const;
		Vec3D operator * (const Vec3D& p_rVec) const;
		Vec3D operator - (void) const;
		Vec3D operator * (const float p_scalar) const;
		Vec3D operator / (const float p_scalar) const;
		
		Vec3D& operator += (const Vec3D& p_rVec);
		Vec3D& operator -= (const Vec3D& p_rVec);
		Vec3D& operator *= (const float p_scalar);
		Vec3D& operator /= (const float p_scalar);
		//---------------------------------------------------------------------

		//---------------------------------------------------------------------
		// PUBLIC MEMBERS
		//---------------------------------------------------------------------
		float	x,y,z;
		//---------------------------------------------------------------------
		
		//---------------------------------------------------------------------
		// CONSTANTS
		//---------------------------------------------------------------------
		static const Vec3D ZERO;
		static const Vec3D ONE;
		static const Vec3D XAXIS;
		static const Vec3D YAXIS;
		static const Vec3D ZAXIS;
		//---------------------------------------------------------------------
};

inline bool operator == (const Vec3D& p_vA, const Vec3D& p_vB)
{
	return p_vA.x == p_vB.x && p_vA.y == p_vB.y && p_vA.z == p_vB.z;
}

inline bool operator != (const Vec3D& p_vA, const Vec3D& p_vB)
{
	return p_vA.x != p_vB.x || p_vA.y != p_vB.y || p_vA.z != p_vB.z;
}

inline float operator|(const Vec3D &a, const Vec3D &b)
	{return a.DotProduct(b);}

inline Vec3D operator^(const Vec3D &a, const Vec3D &b)
	{return a.CrossProduct(b);}
	
inline Vec3D operator*(float s, const Vec3D &v)
	{return Vec3D(v.x * s, v.y * s, v.z * s);}

inline Vec3D& Vec3D::operator =(const Vec3D& rhs)
{
	if (this != &rhs)
	{
		this->x = rhs.x;
		this->y = rhs.y;
		this->z = rhs.z;
	}
	return *this;
}

//---------------------------------------------------------
// Override the + operator.
//---------------------------------------------------------
inline Vec3D Vec3D::operator+(const Vec3D& p_rVec) const
{
	Vec3D vResult;
	vResult.x = x + p_rVec.x;
	vResult.y = y + p_rVec.y;
	vResult.z = z + p_rVec.z;
	return vResult;
}


//---------------------------------------------------------
// Override the + operator.
// usage: projects this vector into another
//---------------------------------------------------------
inline Vec3D Vec3D::operator*(const Vec3D& p_rVec) const
{
	Vec3D vResult;
	vResult.x = x * p_rVec.x;
	vResult.y = y * p_rVec.y;
	vResult.z = z * p_rVec.z;
	return vResult;
}

}

#endif
