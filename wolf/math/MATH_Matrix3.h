/*
 *  MATH_Matrix3.h
 *  OOI_Common
 *
 *  Created by Cesar Castro on 10-06-29.
 *  Copyright 2010 Other Ocean Interactive. All rights reserved.
 *
 */

#ifndef MATH_MATRIX3_H
#define MATH_MATRIX3_H

#include "MATH_Vec3D.h"

namespace math
{
	class Matrix3
	{
	public:
		//-------------------------------------------------------------------------
		// PUBLIC INTERFACE
		//-------------------------------------------------------------------------
		Matrix3() {} // For optimization reasons, this doesn't initialize to anything
		Matrix3(float p_f00, float p_f01, float p_f02, 
				float p_f10, float p_f11, float p_f12,
				float p_f20, float p_f21, float p_f22);
		
		void SetIdentity();
		
		//
		//sets the matrix with this data.
		void SetMatrix(float* p_pData);
		void SetMatrix(const Matrix3& p_mMatrix);
		
		// Transpose
		void Transpose();
		Matrix3 GetTranspose() const;
		
		// Inverse
		void Inverse();
		Matrix3 GetInverse() const;
		
		// Returns the result of multiplying p_m by this.  Note the syntax is kind
		// of misleading because this matrix is multiplied from the LEFT by the
		// matrix p_m.
		Matrix3 operator*(const Matrix3& p_m) const;
		
		//----------------------------------------------------------
		// Method:     Determinant
		// 
		// Computes and returns the matrix determinant
		//----------------------------------------------------------
		float Determinant() const
		{
			float fDeterminant = m[0] * (m[4] * m[8] - m[7] * m[5]);
			fDeterminant    += m[3] * (m[7] * m[2] - m[1] * m[8]);
			fDeterminant    += m[6] * (m[1] * m[5] - m[4] * m[2]);
			
			return fDeterminant;
		}
		
		// Returns the result of multiplying p_v by the partial 3x3 matrix and
		// then adding the translation component.  Note  the syntax is kind of
		// misleading because the matrix (this) is multiplied from the LEFT
		// by the vector p_v.
		inline Vec3D operator*(const Vec3D& p_v) const
		{
			Vec3D vRet;                                             
			vRet.x = (p_v.x * m[0]) + (p_v.y * m[3]) + (p_v.z * m[6]);
			vRet.y = (p_v.x * m[1]) + (p_v.y * m[4]) + (p_v.z * m[7]);
			vRet.z = (p_v.x * m[2]) + (p_v.y * m[5]) + (p_v.z * m[8]);
			return vRet; 
		}
		
		const float* AsArray() const { return m; }
		
		// Static constants
		static const Matrix3 IDENTITY;
		//-------------------------------------------------------------------------
		
		//-------------------------------------------------------------------------
		// PUBLIC MEMBERS
		//-------------------------------------------------------------------------
		float		m[9];
		//-------------------------------------------------------------------------
	};		
}

#endif // MATH_MATRIX3_H


