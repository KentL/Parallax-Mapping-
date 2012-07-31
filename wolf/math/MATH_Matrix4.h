//-----------------------------------------------------------------------------
// File:			MATH_Matrix4.h
// Original Author:	Gordon Wood
//
// Matrix class (finally!)
//-----------------------------------------------------------------------------
#ifndef MATH_MATRIX4_H
#define MATH_MATRIX4_H

#include "MATH_Vec3D.h"
#include "MATH_Matrix3.h"
#include <stdio.h>

namespace math
{
class Matrix4
{
public:
	//-------------------------------------------------------------------------
	// PUBLIC INTERFACE
	//-------------------------------------------------------------------------
	Matrix4() {} // For optimization reasons, this doesn't initialize to anything
	Matrix4(float p_f00, float p_f01, float p_f02, float p_f03, 
			float p_f10, float p_f11, float p_f12, float p_f13,
			float p_f20, float p_f21, float p_f22, float p_f23,
			float p_f30, float p_f31, float p_f32, float p_f33);
	
	void SetIdentity();
	
	//
	//sets the matrix with this data.
	void SetMatrix(float* p_pData);	
	void SetMatrix(const Matrix4& p_mMatrix);	

    
    // Transpose
	void Transpose();
	Matrix4 GetTranspose() const;      

	// Inverse
	void Inverse();
	Matrix4 GetInverse() const;
    
	// Translate
	void Translate(float p_fX, float p_fY, float p_fZ);
	void Translate(const math::Vec3D& p_vTrans);
	void SetTranslation(float p_fX, float p_fY, float p_fZ);
	void SetTranslation(const math::Vec3D& p_vPos);
	math::Vec3D GetTranslation() const { return math::Vec3D(m[12],m[13],m[14]); }
	math::Vec3D GetDirVector() const { return math::Vec3D(m[0],m[1],m[2]); }
	math::Vec3D GetUpVector() const { return math::Vec3D(m[4],m[5],m[6]); }
	math::Vec3D GetEyeVector() const { return math::Vec3D(m[8],m[9],m[10]); }
	
	void SetDirVector(math::Vec3D p_Vec)
	{
		m[0] = p_Vec.x;
		m[1] = p_Vec.y;
		m[2] = p_Vec.z;
	}
	
	void SetUpVector(math::Vec3D p_Vec)
	{
		m[4] = p_Vec.x;
		m[5] = p_Vec.y;
		m[6] = p_Vec.z;
	}
	
	void SetEyeVector(math::Vec3D p_Vec)
	{
		m[8] = p_Vec.x;
		m[9] = p_Vec.y;
		m[10] = p_Vec.z;
	}

	void Scale(float p_fValue)
	{
		m[0] *= p_fValue;
		m[1] *= p_fValue;
		m[2] *= p_fValue;
		
		m[4] *= p_fValue;
		m[5] *= p_fValue;
		m[6] *= p_fValue;
		
		m[8] *= p_fValue;
		m[9] *= p_fValue;
		m[10] *= p_fValue;
	}
	
	math::Vec3D GetScale()
	{
		return math::Vec3D(m[0],m[5],m[10]);
	}
	
	const float* AsArray() const { return m; }
	void AsFloatArray( float *p_pfSrcArray ) const;
   	// Static helper "constructors"
	static Matrix4 ScaleMatrix(float p_fX, float p_fY, float p_fZ);
	static Matrix4 TranslationMatrix(float p_fX, float p_fY, float p_fZ);
	static Matrix4 TranslationMatrix(const Vec3D& p_vTrans);
	static Matrix4 RotateXMatrix(float p_fAngle); // radians!
	static Matrix4 RotateYMatrix(float p_fAngle); // radians!
	static Matrix4 RotateZMatrix(float p_fAngle); // radians!
	static Matrix4 RotateAxisMatrix(const math::Vec3D& p_vAxis, float p_fAngle);
	static Matrix4 LookAtMatrixLHS(const math::Vec3D& p_vEye,const math::Vec3D& p_vAt, const math::Vec3D& p_vUp);
	static Matrix4 LookAtMatrixRHS(const math::Vec3D& p_vEye,const math::Vec3D& p_vAt, const math::Vec3D& p_vUp);
	static Matrix4 PerspectiveMatrixLHS(float p_fFOV, float p_fAspectRatio, float p_fNear, float p_fFar, bool p_bRotate);
	static Matrix4 PerspectiveMatrixRHS(float p_fFOV, float p_fAspectRatio, float p_fNear, float p_fFar, bool p_bRotate);
	static Matrix4 OrthographicMatrix(float p_fLeft, float p_fRight, float p_fBottom, float p_fTop, float p_fNear, float p_fFar, bool p_bRotate);
	static Matrix4 OrthographicMatrix(float p_fWidth, float p_fHeight, float p_fNear, float p_fFar, bool p_bRotate);
	static Matrix4 NewOrthoMatrix(float p_fWidth, float p_fHeight, float p_fNear, float p_fFar, bool p_bRotate);

	
	// Operators  
	float* operator[](const int p_iRow) { return &m[p_iRow*4]; }
	const float* operator[](const int p_iRow) const { return &m[p_iRow*4]; }
	
	inline bool operator==(const Matrix4& p_m) const
	{
		for( int i = 0; i < 16; i++ )
			if( p_m.m[i] != m[i] )
				return false;
		
		return true;
	}
	
	// Returns the result of multiplying p_m by this.  Note the syntax is kind
	// of misleading because this matrix is multiplied from the LEFT by the
	// matrix p_m.
	inline Matrix4 operator*(const Matrix4& p_m) const;

	// Returns the result of multiplying p_v by the partial 3x3 matrix and
	// then adding the translation component.  Note  the syntax is kind of
	// misleading because the matrix (this) is multiplied from the LEFT
	// by the vector p_v.
	inline Vec3D operator*(const Vec3D& p_v) const;
	
	void Print()
	{
		printf("------------------\n");
		printf("X : %f %f %f %f \n",m[0],m[1],m[2],m[3]);
		printf("Y : %f %f %f %f \n",m[4],m[5],m[6],m[7]);
		printf("Z : %f %f %f %f \n",m[8],m[9],m[10],m[11]);
		printf("T : %f %f %f %f \n",m[12],m[13],m[14],m[15]);
		
	}
	
	void ToMatrix3(Matrix3& p_mOut) const
	{
		p_mOut.m[0] = m[0];
		p_mOut.m[1] = m[1];
		p_mOut.m[2] = m[2];
		
		p_mOut.m[3] = m[4];
		p_mOut.m[4] = m[5];
		p_mOut.m[5] = m[6];
		
		p_mOut.m[6] = m[8];
		p_mOut.m[7] = m[9];
		p_mOut.m[8] = m[10];
	}
	
	// Static constants
	static const Matrix4 IDENTITY;
	//-------------------------------------------------------------------------
	
	//-------------------------------------------------------------------------
	// PUBLIC MEMBERS
	//-------------------------------------------------------------------------
	float		m[16];	
	//-------------------------------------------------------------------------
};

}

#include "MATH_Matrix4.inl"

#endif


