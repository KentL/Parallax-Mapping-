//-----------------------------------------------------------------------------
// File:			MATH_Matrix4.cpp
// Original Author:	Gordon Wood
//
// See header for notes
//-----------------------------------------------------------------------------
#include "MATH_Matrix4.h"
#include "W_Math.h"
#include <math.h>
#include <string.h>

namespace math
{
const Matrix4 Matrix4::IDENTITY(1, 0, 0, 0, 
								0, 1, 0, 0,
								0, 0, 1, 0,
								0, 0, 0, 1); 
								
//----------------------------------------------------------
// Method:		Matrix4
// Parameters:	components - all the components of the matrix
//
// Constructor taking in all the components of the matrix
//----------------------------------------------------------
Matrix4::Matrix4(float p_f00, float p_f01, float p_f02, float p_f03, 
				 float p_f10, float p_f11, float p_f12, float p_f13,
				 float p_f20, float p_f21, float p_f22, float p_f23,
				 float p_f30, float p_f31, float p_f32, float p_f33)
{
	m[0] = p_f00; m[1] = p_f01; m[2] = p_f02; m[3] = p_f03;
	m[4] = p_f10; m[5] = p_f11; m[6] = p_f12; m[7] = p_f13;
	m[8] = p_f20; m[9] = p_f21; m[10] = p_f22; m[11] = p_f23;
	m[12] = p_f30; m[13] = p_f31; m[14] = p_f32; m[15] = p_f33;
}

//----------------------------------------------------------
// Method:     SetIdentity
// 
// Sets this matrix to the identity matrix
//----------------------------------------------------------
void Matrix4::SetIdentity()
{
	*this = Matrix4::IDENTITY;
}

//----------------------------------------------------------
// Method:     ScaleMatrix
// Parameters: p_fX - x scale
//             p_fY - y scale
//             p_fZ - z scale
// 
// Creates a scale matrix
//----------------------------------------------------------
Matrix4 Matrix4::ScaleMatrix(float p_fX, float p_fY, float p_fZ)
{
	Matrix4 mRet;
	
	mRet.m[ 0] = p_fX; mRet.m[ 1] = 0.0f;  mRet.m[ 2] = 0.0f; mRet.m[ 3] = 0.0f;
	mRet.m[ 4] = 0.0f; 	mRet.m[ 5] = p_fY;  mRet.m[ 6] = 0.0f; mRet.m[ 7] = 0.0f;
	mRet.m[ 8] = 0.0f; 	mRet.m[ 9] = 0.0f;  mRet.m[10] = p_fZ; mRet.m[11] = 0.0f;
	mRet.m[12] = 0.0f; 	mRet.m[13] = 0.0f;  mRet.m[14] = 0.0f; mRet.m[15] = 1.0f;
	
	return mRet;
}

//----------------------------------------------------------
// Method:     TranslationMatrix
// Parameters: p_fX - x trans
//             p_fY - y trans
//             p_fZ - z trans
// 
// Creates a translation matrix
//----------------------------------------------------------
Matrix4 Matrix4::TranslationMatrix(float p_fX, float p_fY, float p_fZ)
{
	Matrix4 mRet;
	
	mRet.m[ 0] = 1.0f; 	mRet.m[ 1] = 0.0f;  mRet.m[ 2] = 0.0f; mRet.m[ 3] = 0.0f;
	mRet.m[ 4] = 0.0f; 	mRet.m[ 5] = 1.0f;  mRet.m[ 6] = 0.0f; mRet.m[ 7] = 0.0f;
	mRet.m[ 8] = 0.0f; 	mRet.m[ 9] = 0.0f;  mRet.m[10] = 1.0f; mRet.m[11] = 0.0f;
	mRet.m[12] = p_fX; mRet.m[13] = p_fY;  mRet.m[14] = p_fZ; mRet.m[15] = 1.0f;
	
	return mRet;
}

//----------------------------------------------------------
// Method:     TranslationMatrix
// Parameters: p_vTrans - the translation vector
// 
// Creates a translation matrx
//----------------------------------------------------------
Matrix4 Matrix4::TranslationMatrix(const Vec3D& p_vTrans)
{     
	Matrix4 mRet;
	
	mRet.m[ 0] = 1.0f; 	mRet.m[ 1] = 0.0f;  mRet.m[ 2] = 0.0f; mRet.m[ 3] = 0.0f;
	mRet.m[ 4] = 0.0f; 	mRet.m[ 5] = 1.0f;  mRet.m[ 6] = 0.0f; mRet.m[ 7] = 0.0f;
	mRet.m[ 8] = 0.0f; 	mRet.m[ 9] = 0.0f;  mRet.m[10] = 1.0f; mRet.m[11] = 0.0f;
	mRet.m[12] = p_vTrans.x; mRet.m[13] = p_vTrans.y; mRet.m[14] = p_vTrans.z; mRet.m[15] = 1.0f;
	
	return mRet;
}

//----------------------------------------------------------
// Method:     RotateXMatrix
// Parameters: p_fAngle - angle to rotate (in radians)
// 
// Creates a rotation matrix around the x axis
//----------------------------------------------------------
Matrix4 Matrix4::RotateXMatrix(float p_fAngle)
{    
	Matrix4 mRet;
	
	float fCos	= cosf(p_fAngle);
    float fSin	= sinf(p_fAngle);  

 	mRet.m[ 0] = 1.0f; mRet.m[ 1] = 0.0f; mRet.m[ 2] = 0.0f; mRet.m[ 3] = 0.0f;
	mRet.m[ 4] = 0.0f; mRet.m[ 5] = fCos;mRet.m[ 6] = fSin; mRet.m[ 7] = 0.0f;
	mRet.m[ 8] = 0.0f; mRet.m[ 9] = -fSin; mRet.m[10] = fCos; mRet.m[11] = 0.0f;
	mRet.m[12] = 0.0f; mRet.m[13] = 0.0f; mRet.m[14] = 0.0f; mRet.m[15] = 1.0f;
	
	return mRet;
}

//----------------------------------------------------------
// Method:     RotateYMatrix
// Parameters: p_fAngle - angle to rotate (in radians)
// 
// Creates a rotation matrix around the y axis
//----------------------------------------------------------
Matrix4 Matrix4::RotateYMatrix(float p_fAngle)
{  
	Matrix4 mRet;
	
	float fCos	= cosf(p_fAngle);
    float fSin	= sinf(p_fAngle);  

 	mRet.m[ 0] = fCos; mRet.m[ 1] = 0.0f; mRet.m[ 2] = -fSin; mRet.m[ 3] = 0.0f;
	mRet.m[ 4] = 0.0f; mRet.m[ 5] = 1.0f; mRet.m[ 6] = 0.0f; mRet.m[ 7] = 0.0f;
	mRet.m[ 8] = fSin; mRet.m[ 9] = 0.0f; mRet.m[10] = fCos; mRet.m[11] = 0.0f;
	mRet.m[12] = 0.0f; mRet.m[13] = 0.0f; mRet.m[14] = 0.0f; mRet.m[15] = 1.0f;
	
	return mRet;
}

//----------------------------------------------------------
// Method:     RotateZMatrix
// Parameters: p_fAngle - angle to rotate (in radians)
// 
// Creates a rotation matrix around the z axis
//----------------------------------------------------------
Matrix4 Matrix4::RotateZMatrix(float p_fAngle)
{    
	Matrix4 mRet;
	
	float fCos	= cosf(p_fAngle);
    float fSin	= sinf(p_fAngle);

	mRet.m[ 0] = fCos; mRet.m[ 1] = fSin; mRet.m[ 2] = 0.0f; mRet.m[ 3] = 0.0f;
	mRet.m[ 4] =-fSin; mRet.m[ 5] = fCos; mRet.m[ 6] = 0.0f; mRet.m[ 7] = 0.0f;
	mRet.m[ 8] = 0.0f; mRet.m[ 9] = 0.0f; mRet.m[10] = 1.0f; mRet.m[11] = 0.0f;
	mRet.m[12] = 0.0f; mRet.m[13] = 0.0f; mRet.m[14] = 0.0f; mRet.m[15] = 1.0f;
	
	return mRet;
}

//----------------------------------------------------------
// Method:     Transpose
// 
// Transposes this matrix
//----------------------------------------------------------
void Matrix4::Transpose()
{
	Matrix4 mTmp;
	
	mTmp.m[0] = m[0]; mTmp.m[1] = m[4]; mTmp.m[2] = m[8]; mTmp.m[3] = m[12];
	mTmp.m[4] = m[1]; mTmp.m[5] = m[5]; mTmp.m[6] = m[9]; mTmp.m[7] = m[13];
	mTmp.m[8] = m[2]; mTmp.m[9] = m[6]; mTmp.m[10] = m[10]; mTmp.m[11] = m[14];
	mTmp.m[12] = m[3]; mTmp.m[13] = m[7]; mTmp.m[14] = m[11]; mTmp.m[15] = m[15];   
	
	*this = mTmp;
}

//----------------------------------------------------------
// Method:     GetTranspose
// 
// Returns the transpose of this matrix
//----------------------------------------------------------
Matrix4 Matrix4::GetTranspose() const
{
	Matrix4 mTmp;
	
	mTmp.m[0] = m[0]; mTmp.m[1] = m[4]; mTmp.m[2] = m[8]; mTmp.m[3] = m[12];
	mTmp.m[4] = m[1]; mTmp.m[5] = m[5]; mTmp.m[6] = m[9]; mTmp.m[7] = m[13];
	mTmp.m[8] = m[2]; mTmp.m[9] = m[6]; mTmp.m[10] = m[10]; mTmp.m[11] = m[14];
	mTmp.m[12] = m[3]; mTmp.m[13] = m[7]; mTmp.m[14] = m[11]; mTmp.m[15] = m[15];   
	
	return mTmp;	
}

//----------------------------------------------------------
// Method:     Inverse
// 
// Changes this matrix to be the inverse of itself
//----------------------------------------------------------
void Matrix4::Inverse()
{
	*this = GetInverse();
}

//----------------------------------------------------------
// Method:     GetInverse
// 
// Returns the inverse of this matrix
//----------------------------------------------------------
Matrix4 Matrix4::GetInverse() const
{
	Matrix4	mTmp;
#ifdef OOI_USE_FLOATING_POINT
	double	det_1;
	double	pos, neg, temp;
#else
	float det_1;
	float pos,neg,temp;
#endif

    /* Calculate the determinant of submatrix A and determine if the
       the matrix is singular as limited by the double precision
       floating-point data representation. */
    pos = neg = 0.0;
    temp =  m[ 0] * m[ 5] * m[10];
    if (temp >= 0.0) pos += temp; else neg += temp;
    temp =  m[ 4] * m[ 9] * m[ 2];
    if (temp >= 0.0) pos += temp; else neg += temp;
    temp =  m[ 8] * m[ 1] * m[ 6];
    if (temp >= 0.0) pos += temp; else neg += temp;
    temp = -m[ 8] * m[ 5] * m[ 2];
    if (temp >= 0.0) pos += temp; else neg += temp;
    temp = -m[ 4] * m[ 1] * m[10];
    if (temp >= 0.0) pos += temp; else neg += temp;
    temp = -m[ 0] * m[ 9] * m[ 6];
    if (temp >= 0.0) pos += temp; else neg += temp;
    det_1 = pos + neg;

    /* Is the submatrix A singular? */  
#define D_ABS(d)	((d)<0?(-(d)):(d))

    if ((det_1 == 0.0) || (D_ABS(det_1 / (pos - neg)) < 1.0e-15))
	{
        /* Matrix M has no inverse */
 //       DebugPrintf("Warning: Matrix has no inverse : singular matrix\n");
        return *this;
    }
    else
	{
        /* Calculate inverse(A) = adj(A) / det(A) */
        det_1 = 1.0f / det_1;
        mTmp.m[ 0] =   ( m[ 5] * m[10] - m[ 9] * m[ 6] ) * (float)det_1;
        mTmp.m[ 1] = - ( m[ 1] * m[10] - m[ 9] * m[ 2] ) * (float)det_1;
        mTmp.m[ 2] =   ( m[ 1] * m[ 6] - m[ 5] * m[ 2] ) * (float)det_1;
        mTmp.m[ 4] = - ( m[ 4] * m[10] - m[ 8] * m[ 6] ) * (float)det_1;
        mTmp.m[ 5] =   ( m[ 0] * m[10] - m[ 8] * m[ 2] ) * (float)det_1;
        mTmp.m[ 6] = - ( m[ 0] * m[ 6] - m[ 4] * m[ 2] ) * (float)det_1;
        mTmp.m[ 8] =   ( m[ 4] * m[ 9] - m[ 8] * m[ 5] ) * (float)det_1;
        mTmp.m[ 9] = - ( m[ 0] * m[ 9] - m[ 8] * m[ 1] ) * (float)det_1;
        mTmp.m[10] =   ( m[ 0] * m[ 5] - m[ 4] * m[ 1] ) * (float)det_1;

        /* Calculate -C * inverse(A) */
        mTmp.m[12] = - ( m[12] * mTmp.m[ 0] + m[13] * mTmp.m[ 4] + m[14] * mTmp.m[ 8] );
        mTmp.m[13] = - ( m[12] * mTmp.m[ 1] + m[13] * mTmp.m[ 5] + m[14] * mTmp.m[ 9] );
        mTmp.m[14] = - ( m[12] * mTmp.m[ 2] + m[13] * mTmp.m[ 6] + m[14] * mTmp.m[10] );

        /* Fill in last row */
        mTmp.m[ 3] = 0.0f;
		mTmp.m[ 7] = 0.0f;
		mTmp.m[11] = 0.0f;
        mTmp.m[15] = 1.0f;
	}

	return mTmp; 
}

//----------------------------------------------------------
// Method:     LookAtLHS
// Parameters: p_vEye - the location of the eye
//             p_vAt - what we're looking at
//             p_vUp - up
// 
// Creates a look-at modelview matrix in a left-handed-system
//----------------------------------------------------------
Matrix4 Matrix4::LookAtMatrixLHS(const math::Vec3D& p_vEye,const math::Vec3D& p_vAt, const math::Vec3D& p_vUp)
{
	math::Vec3D f, vUpActual, s, u;
	Matrix4	t;
	Matrix4 mRet;
	
	f = p_vEye - p_vAt;
	float len = sqrtf((f.x) * (f.x) + (f.y) * (f.y) + (f.z) * (f.z)); //normalizing in floating point, since fixed is not gonna cut it
	f /= len;
	
	vUpActual = p_vUp;
	len = sqrtf((vUpActual.x) * (vUpActual.x) + (vUpActual.y) * (vUpActual.y) + (vUpActual.z) * (vUpActual.z)); //normalizing in floating point, since fixed is not gonna cut it
	vUpActual /= len;
	
	s = f.CrossProduct(vUpActual);
	u = s.CrossProduct(f);

	mRet.m[ 0] = s.x;
	mRet.m[ 1] = u.x;
	mRet.m[ 2] = -f.x;
	mRet.m[ 3] = 0;

	mRet.m[ 4] = s.y;
	mRet.m[ 5] = u.y;
	mRet.m[ 6] = -f.y;
	mRet.m[ 7] = 0;

	mRet.m[ 8] = s.z;
	mRet.m[ 9] = u.z;
	mRet.m[10] = -f.z;
	mRet.m[11] = 0;

	mRet.m[12] = 0;
	mRet.m[13] = 0;
	mRet.m[14] = 0;
	mRet.m[15] = 1;

	t = TranslationMatrix(-p_vEye.x, -p_vEye.y, -p_vEye.z);
	mRet = mRet * t;
	return mRet;
}

//----------------------------------------------------------
// Method:     LookAtRHS
// Parameters: p_vEye - the location of the eye
//             p_vAt - what we're looking at
//             p_vUp - up
// 
// Creates a look-at modelview matrix in a right-handed-system
//----------------------------------------------------------
Matrix4 Matrix4::LookAtMatrixRHS(const math::Vec3D& p_vEye,const math::Vec3D& p_vAt, const math::Vec3D& p_vUp)
{
	math::Vec3D f, vUpActual, s, u, left;
	Matrix4	t;
	Matrix4 mRet;
	
	f = p_vAt - p_vEye;
	float len = sqrtf((f.x) * (f.x) + (f.y) * (f.y) + (f.z) * (f.z)); //normalizing in floating point, since fixed is not gonna cut it
	f /= len;
	
	// compute temporal up vector based on the forward vector
    // watch out when look up/down at 90 degree
    // for example, forward vector is on the Y axis
	if( fabsf(f.x) < 1.19209e-007 && fabsf(f.z) < 1.19209e-007 )
    {
        // forward vector is pointing +Y axis
        if(f.y > 0)
			vUpActual = math::Vec3D(0, 0, 1);
        // forward vector is pointing -Y axis
        else
			vUpActual = math::Vec3D(0, 0, -1);
    }
    // in general, up vector is straight up
    else
    {
       vUpActual = p_vUp;
    }

	left = p_vUp.CrossProduct(f);
	len = sqrtf((left.x) * (left.x) + (left.y) * (left.y) + (left.z) * (left.z)); //normalizing in floating point, since fixed is not gonna cut it
	left /= len;

	vUpActual = f.CrossProduct(left);
	len = sqrtf((vUpActual.x) * (vUpActual.x) + (vUpActual.y) * (vUpActual.y) + (vUpActual.z) * (vUpActual.z)); //normalizing in floating point, since fixed is not gonna cut it
	vUpActual /= len;
	
	s = f.CrossProduct(vUpActual);
	u = s.CrossProduct(f);

	mRet.m[ 0] = s.x;
	mRet.m[ 1] = u.x;
	mRet.m[ 2] = -f.x;
	mRet.m[ 3] = 0;

	mRet.m[ 4] = s.y;
	mRet.m[ 5] = u.y;
	mRet.m[ 6] = -f.y;
	mRet.m[ 7] = 0;

	mRet.m[ 8] = s.z;
	mRet.m[ 9] = u.z;
	mRet.m[10] = -f.z;
	mRet.m[11] = 0;

	mRet.m[12] = 0;
	mRet.m[13] = 0;
	mRet.m[14] = 0;
	mRet.m[15] = 1;

	t = TranslationMatrix(-p_vEye.x, -p_vEye.y, -p_vEye.z);
	mRet = mRet * t;
	return mRet;
}

//----------------------------------------------------------
// Method:     PerspectiveMatrixLHS
// Parameters: p_fFOV - field of view
//             p_fAspectRatio - aspect ratio
//             p_fNear - near limit
//             p_fFar - far limit
//             p_bRotate - ??
// 
// Construct a perspective matrix for a left-handed-system
//----------------------------------------------------------
Matrix4 Matrix4::PerspectiveMatrixLHS(float p_fFOV, float p_fAspectRatio, float p_fNear, float p_fFar, bool p_bRotate)
{
	float fHeight = (2.0f*p_fNear) * tanf(p_fFOV * 0.5f);
	float fWidth	= fHeight * p_fAspectRatio;
	
	if (p_bRotate) 
	{
		fWidth = fHeight; 
		fHeight = fHeight / p_fAspectRatio;
	}
	
	float n2 = 2.0f * p_fNear;
	float rcpnmf = 1.0f / (p_fNear - p_fFar);
	
	Matrix4 mRet;
	if (p_bRotate)
	{
		mRet.m[0] = 0;				mRet.m[4]= -n2/fWidth;	mRet.m[8]=0;	mRet.m[12]=0;
		mRet.m[1] = n2 / fHeight;	mRet.m[5]=0;			mRet.m[9]=0;	mRet.m[13]=0;
	}
	else
	{
		mRet.m[0] = n2 / fWidth;	mRet.m[4]=0;			mRet.m[8]=0;	mRet.m[12]=0;
		mRet.m[1] = 0;				mRet.m[5]=n2/fHeight;	mRet.m[9]=0;	mRet.m[13]=0;
	}
	
	mRet.m[2] = 0;	mRet.m[6]=0;	mRet.m[10]=(p_fFar+p_fNear) * rcpnmf;	mRet.m[14]=(p_fFar*rcpnmf)*n2;
	mRet.m[3] = 0;	mRet.m[7]=0;	mRet.m[11]=-1.0f;	mRet.m[15]=0;
	
	mRet.m[10] = mRet.m[10] * -1.0f;
	mRet.m[11] = 1.0f;
	
	return mRet;	
}

//----------------------------------------------------------
// Method:     PerspectiveMatrixRHS
// Parameters: p_fFOV - field of view
//             p_fAspectRatio - apsect ratio
//             p_fNear - near limit
//             p_fFar - far limit
//             p_bRotate - ??
// 
// Construct a perspective matrix for a right-handed-system
//----------------------------------------------------------
Matrix4 Matrix4::PerspectiveMatrixRHS(float p_fFOV, float p_fAspectRatio, float p_fNear, float p_fFar, bool p_bRotate)
{
	Matrix4 mRet;
	
	float f, n, fRealAspect;
	
	if (p_bRotate)
		fRealAspect = 1.0f / p_fAspectRatio;
	else
		fRealAspect = p_fAspectRatio;
	
	// cotangent(a) == 1.0f / tan(a);
	f = 1.0f / tanf( p_fFOV * 0.5f );

	n = 1.0f / (p_fNear - p_fFar);
	
	mRet.m[ 0] = f / fRealAspect;
	mRet.m[ 1] = 0;
	mRet.m[ 2] = 0;
	mRet.m[ 3] = 0;
	
	mRet.m[ 4] = 0;
	mRet.m[ 5] = f;
	mRet.m[ 6] = 0;
	mRet.m[ 7] = 0;
	
	mRet.m[ 8] = 0;
	mRet.m[ 9] = 0;
	mRet.m[10] = (p_fFar + p_fNear) * n;
	mRet.m[11] = -1;
	
	mRet.m[12] = 0;
	mRet.m[13] = 0;
	mRet.m[14] = (2.0f * p_fFar * p_fNear) * n;
	mRet.m[15] = 0;
	
	if (p_bRotate)
	{
		Matrix4 mRotation, mTemp = mRet;
		mRotation = Matrix4::RotateZMatrix( -90.0f * PI / 180.f);
		mRet = mTemp * mRotation;
	}
	
	return mRet;
	
}

//----------------------------------------------------------
// Method:     Translate
// Parameters: p_fX - x component
//             p_fY - y component
//             p_fZ - z component
// 
// Translate the matrix
//----------------------------------------------------------
void Matrix4::Translate(float p_fX, float p_fY, float p_fZ)
{
	m[12] += p_fX;
	m[13] += p_fY;
	m[14] += p_fZ;
}

//----------------------------------------------------------
// Method:     Translate
// Parameters: p_vTrans - the translation vector
// 
// Translate the matrix
//----------------------------------------------------------
void Matrix4::Translate(const math::Vec3D& p_vTrans)
{
	m[12] += p_vTrans.x;
	m[13] += p_vTrans.y;
	m[14] += p_vTrans.z;
}
	
//----------------------------------------------------------
// Method:     SetTranslation
// Parameters: p_fX - x component
//             p_fY - y component
//             p_fZ - z component
// 
// Sets the translation of the matrix (not relative, like Translate)
//----------------------------------------------------------
void Matrix4::SetTranslation(float p_fX, float p_fY, float p_fZ)
{
	m[12] = p_fX;
	m[13] = p_fY;
	m[14] = p_fZ;
}

//----------------------------------------------------------
// Method:     SetTranslation
// Parameters: p_vTrans - the translation vector
// 
// Sets the translation of the matrix (not relative, like Translate)
//----------------------------------------------------------
void Matrix4::SetTranslation(const math::Vec3D& p_vPos)
{
	m[12] = p_vPos.x;
	m[13] = p_vPos.y;
	m[14] = p_vPos.z;
}


void Matrix4::SetMatrix(const Matrix4& p_mMatrix)
{
	memcpy(&m[0],&p_mMatrix.m[0],16*sizeof(float));
}


void Matrix4::SetMatrix(float* p_pData)
{
	memcpy(&m[0],p_pData,16*sizeof(float));
}

Matrix4 Matrix4::RotateAxisMatrix(const math::Vec3D& p_vAxis, float p_fAngle)
{
	Matrix4 mRet = IDENTITY;
	float    t, ss, xx, yy, zz;
    float    t01;
    float    s2;
	
	float fCosVal = cosf(p_fAngle);
	float fSinVal = sinf(p_fAngle);
	
    t = 1.0f - fCosVal;
    ss = fSinVal;
    xx = p_vAxis.x;
    yy = p_vAxis.y;
    zz = p_vAxis.z;
	
    t01 = xx * xx * t;
    mRet.m[0] = t01 + fCosVal;
	
    t01 = yy * yy * t;
    mRet.m[5] = t01 + fCosVal;
	
    t01 = zz * zz * t;
    mRet.m[10] = t01 + fCosVal;
	
    t01 = t * xx * yy;
    s2 = ss * zz;
    mRet.m[1] = t01 + s2;
    mRet.m[4] = t01 - s2;
	
    t01 = t * xx * zz;
    s2 = ss * yy;
    mRet.m[2] = t01 - s2;
    mRet.m[8] = t01 + s2;
	
    t01 = t * yy * zz;
    s2 = ss * xx;
    mRet.m[6] = t01 + s2;
    mRet.m[9] = t01 - s2;
	
	return mRet;
}

void Matrix4::AsFloatArray( float *p_pfSrcArray ) const
{
	if( p_pfSrcArray == NULL )
		return;
	for( int i=0; i< 16; i++ )
	{
		p_pfSrcArray[i] = m[i];
	}
}

//----------------------------------------------------------
// Method:		OrthographicMatrix
// Parameters:	p_fLeft,p_fRight,p_fBottom,p_fTop - extents of the view
//				p_fNear - value of the near plane
//				p_fFar - value of the far plane
//				p_bRotate - whether to rotate the projection matrix or not (for landscape/portrait)
// 
// Sets up an orthographic projection with the given parameters.
// The orthographics projection is right-handed
//----------------------------------------------------------
Matrix4 Matrix4::OrthographicMatrix(float p_fLeft, float p_fRight, float p_fBottom, float p_fTop, float p_fNear, float p_fFar, bool p_bRotate)
{
	math::Matrix4 m;
	
	m.m[0] = float(2.0f) / ( p_fRight - p_fLeft );
	m.m[1] = 0;
	m.m[2] = 0;
	m.m[3] = 0;
	
	m.m[4] = 0;
	m.m[5] = float(2.0f) / (p_fTop - p_fBottom);
	m.m[6] = 0;
	m.m[7] = 0;
	
	m.m[8] = 0;
	m.m[9] = 0;
	m.m[10] = float(2.0f) / (p_fFar - p_fNear);
	m.m[11] = 0;
	
	m.m[12] = -((p_fRight + p_fLeft) / (p_fRight - p_fLeft));
	m.m[13] = -((p_fTop + p_fBottom) / (p_fTop - p_fBottom));
	m.m[14] = -((p_fFar + p_fNear) / (p_fFar - p_fNear));
	m.m[15] = 1;
	
	if(p_bRotate)
	{
		m = math::Matrix4::RotateZMatrix(DEG_TO_RAD(-90.0)) * m;
	}
	
	return m;
}

//----------------------------------------------------------
// Method:		OrthographicMatrix
// Parameters:	p_fWidth,p_fHeight - size of the view
//				p_fNear - value of the near plane
//				p_fFar - value of the far plane
//				p_bRotate - whether to rotate the projection matrix or not (for landscape/portrait)
// 
// Sets up an orthographic projection with the given parameters.
// The orthographics projection is right-handed
//----------------------------------------------------------
Matrix4 Matrix4::OrthographicMatrix(float p_fWidth, float p_fHeight, float p_fNear, float p_fFar, bool p_bRotate)
{
	math::Matrix4 m;

	m.m[0] = float(2.0f) / p_fWidth;
	m.m[1] = 0;
	m.m[2] = 0;
	m.m[3] = 0;

	m.m[4] = 0;
	m.m[5] = float(2.0f) / p_fHeight;
	m.m[6] = 0;
	m.m[7] = 0;

	m.m[8] = 0;
	m.m[9] = 0;
	m.m[10] = float(2.0f) / (p_fFar - p_fNear);
	m.m[11] = 0;

	m.m[12] = 0;
	m.m[13] = 0;
	m.m[14] = -((p_fFar + p_fNear) / (p_fFar - p_fNear));
	m.m[15] = 1;

	if(p_bRotate)
	{
		m = math::Matrix4::RotateZMatrix(DEG_TO_RAD(-90.0)) * m;
	}

	return m;
}

//----------------------------------------------------------
// Method:		NewOrthoMatrix
// Parameters:	p_fWidth,p_fHeight - size of the view
//				p_fNear - value of the near plane
//				p_fFar - value of the far plane
//				p_bRotate - whether to rotate the projection matrix or not (for landscape/portrait)
// 
// Sets up an orthographic projection with the given parameters.
// The orthographics projection is right-handed
//----------------------------------------------------------
Matrix4 Matrix4::NewOrthoMatrix(float p_fWidth, float p_fHeight, float p_fNear, float p_fFar, bool p_bRotate)
{
	math::Matrix4 m;
	m.m[0] = float(2.0f) / p_fWidth;
	m.m[1] = 0;
	m.m[2] = 0;
	m.m[3] = 0;
	
	m.m[4] = 0;
	m.m[5] = float(2.0f) / p_fHeight;
	m.m[6] = 0;
	m.m[7] = 0;
	
	m.m[8] = 0;
	m.m[9] = 0;
	m.m[10] = float(1.0f) / (p_fNear - p_fFar);
	m.m[11] = 0;
	
	m.m[12] = 0;
	m.m[13] = 0;
	m.m[14] = p_fNear / (p_fNear - p_fFar);
	m.m[15] = 1;

	if(p_bRotate)
	{
		m = math::Matrix4::RotateZMatrix(DEG_TO_RAD(-90.0)) * m;
	}
	
	return m;
}

}
