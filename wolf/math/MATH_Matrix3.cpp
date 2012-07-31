/*
 *  MATH_Matrix3.cpp
 *  OOI_Common
 *
 *  Created by Cesar Castro on 10-06-29.
 *  Copyright 2010 Other Ocean Interactive. All rights reserved.
 *
 */

#include "MATH_Matrix3.h"
#include <math.h>
#include <string.h>

// VFP optimizations on iPhone
#ifdef OOI_PLATFORM_iOS
#include <TargetConditionals.h>
#include "matrix_impl.h"
#endif

#ifndef FLOATS_EQUAL
#define FLOATS_EQUAL(a,b) (fabsf((a)-(b)) < 0.0001f)
#endif

namespace math
{
	const Matrix3 Matrix3::IDENTITY(1, 0, 0, 
									0, 1, 0,
									0, 0, 1); 
	
	//----------------------------------------------------------
	// Method:		Matrix3
	// Parameters:	components - all the components of the matrix
	//
	// Constructor taking in all the components of the matrix
	//----------------------------------------------------------
	Matrix3::Matrix3(float p_f00, float p_f01, float p_f02,
					 float p_f10, float p_f11, float p_f12,
					 float p_f20, float p_f21, float p_f22)
	{
		m[0] = p_f00; m[1] = p_f01; m[2] = p_f02;
		m[3] = p_f10; m[4] = p_f11; m[5] = p_f12;
		m[6] = p_f20; m[7] = p_f21; m[8] = p_f22;
	}
	
	//----------------------------------------------------------
	// Method:     SetIdentity
	// 
	// Sets this matrix to the identity matrix
	//----------------------------------------------------------
	void Matrix3::SetIdentity()
	{
		*this = Matrix3::IDENTITY;
	}
	
	//----------------------------------------------------------
	// Method:     operator*
	// Parameters: p_m - other matrix
	// 
	// Multiplies this matrix by another and returns the result
	//
	// wadee -- Returns the result of multiplying p_m by this.  Note the syntax is kind
	// of misleading because this matrix is multiplied from the LEFT by the
	// matrix p_m.
	//----------------------------------------------------------
	Matrix3 Matrix3::operator*(const Matrix3& p_m) const
	{
		Matrix3 mRet;
		
		mRet.m[0] = m[0]*p_m.m[0] + m[3]*p_m.m[1] + m[6]*p_m.m[2];	                
		mRet.m[1] = m[1]*p_m.m[0] + m[4]*p_m.m[1] + m[7]*p_m.m[2];
		mRet.m[2] = m[2]*p_m.m[0] + m[5]*p_m.m[1] + m[8]*p_m.m[2];
		
		mRet.m[3] = m[0]*p_m.m[3] + m[3]*p_m.m[4] + m[6]*p_m.m[5];
		mRet.m[4] = m[1]*p_m.m[3] + m[4]*p_m.m[4] + m[7]*p_m.m[5];
		mRet.m[5] = m[2]*p_m.m[3] + m[5]*p_m.m[4] + m[8]*p_m.m[5];
		
		mRet.m[6] = m[0]*p_m.m[6] + m[3]*p_m.m[7] + m[6]*p_m.m[8];
		mRet.m[7] = m[1]*p_m.m[6] + m[4]*p_m.m[7] + m[7]*p_m.m[8];
		mRet.m[8] = m[2]*p_m.m[6] + m[5]*p_m.m[7] + m[8]*p_m.m[8];
		
		return mRet;
	}

	//----------------------------------------------------------
	// Method:     Transpose
	// 
	// Transposes this matrix
	//----------------------------------------------------------
	void Matrix3::Transpose()
	{		
		*this = GetTranspose();
	}
	
	//----------------------------------------------------------
	// Method:     GetTranspose
	// 
	// Returns the transpose of this matrix
	//----------------------------------------------------------
	Matrix3 Matrix3::GetTranspose() const
	{
		Matrix3 mTmp;
		
		mTmp.m[0] = m[0]; mTmp.m[1] = m[3]; mTmp.m[2] = m[6];
		mTmp.m[3] = m[1]; mTmp.m[4] = m[4]; mTmp.m[5] = m[7];
		mTmp.m[6] = m[2]; mTmp.m[7] = m[5]; mTmp.m[8] = m[8];   
		
		return mTmp;	
	}	
	
	//----------------------------------------------------------
	// Method:     Inverse
	// 
	// Changes this matrix to be the inverse of itself
	//----------------------------------------------------------
	void Matrix3::Inverse()
	{
		*this = GetInverse();
	}
	
	//----------------------------------------------------------
	// Method:     GetInverse
	// 
	// Returns the inverse of this matrix
	//----------------------------------------------------------
	Matrix3 Matrix3::GetInverse() const
	{
		float fDeterminant = Determinant();
		if (FLOATS_EQUAL(fDeterminant, 0.0f))
		{
			/* Matrix M has no inverse */
			//       DebugPrintf("Warning: Matrix has no inverse : singular matrix\n");
			return *this;
		}
		else
		{
			Matrix3	mInverse;

			mInverse.m[0] = (m[4]*m[8] - m[7]*m[5]) / fDeterminant;
			mInverse.m[1] = (m[7]*m[2] - m[1]*m[8]) / fDeterminant;
			mInverse.m[2] = (m[1]*m[5] - m[4]*m[2]) / fDeterminant;
			mInverse.m[3] = (m[5]*m[6] - m[8]*m[3]) / fDeterminant;
			mInverse.m[4] = (m[8]*m[0] - m[2]*m[6]) / fDeterminant;
			mInverse.m[5] = (m[2]*m[3] - m[5]*m[0]) / fDeterminant;
			mInverse.m[6] = (m[3]*m[7] - m[6]*m[4]) / fDeterminant;
			mInverse.m[7] = (m[6]*m[1] - m[0]*m[7]) / fDeterminant;
			mInverse.m[8] = (m[0]*m[4] - m[3]*m[1]) / fDeterminant;
			
			return mInverse;
		}
	}	
	
	void Matrix3::SetMatrix(const Matrix3& p_mMatrix)
	{
		memcpy(&m[0],&p_mMatrix.m[0],9*sizeof(float));
	}
	
	
	void Matrix3::SetMatrix(float* p_pData)
	{
		memcpy(&m[0],p_pData,9*sizeof(float));
	}

}



