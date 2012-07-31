
// VFP optimizations on iPhone
#ifdef OOI_PLATFORM_iOS
#include <TargetConditionals.h>
#include "matrix_impl.h"
#endif


namespace math
{

	inline Vec3D Matrix4::operator*(const Vec3D& p_v) const
	{
		Vec3D vRet;                                             
		vRet.x = (p_v.x * m[0]) + (p_v.y * m[4]) + (p_v.z * m[8]) + m[12];
		vRet.y = (p_v.x * m[1]) + (p_v.y * m[5]) + (p_v.z * m[9]) + m[13];
		vRet.z = (p_v.x * m[2]) + (p_v.y * m[6]) + (p_v.z * m[10]) + m[14];
		return vRet; 
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
inline Matrix4 Matrix4::operator*(const Matrix4& p_m) const
{
	Matrix4 mRet;
	
#if defined(OOI_PLATFORM_iOS) && (TARGET_IPHONE_SIMULATOR == 0) && (TARGET_OS_IPHONE == 1) && defined(OOI_USE_FLOATING_POINT)
	Matrix4Mul(m,p_m.m,mRet.m);
#else
	mRet.m[ 0] = m[ 0]*p_m.m[ 0] + m[ 4]*p_m.m[ 1] + m[ 8]*p_m.m[ 2] + m[12]*p_m.m[ 3];	                
	mRet.m[ 1] = m[ 1]*p_m.m[ 0] + m[ 5]*p_m.m[ 1] + m[ 9]*p_m.m[ 2] + m[13]*p_m.m[ 3];
	mRet.m[ 2] = m[ 2]*p_m.m[ 0] + m[ 6]*p_m.m[ 1] + m[10]*p_m.m[ 2] + m[14]*p_m.m[ 3];
	mRet.m[ 3] = m[ 3]*p_m.m[ 0] + m[ 7]*p_m.m[ 1] + m[11]*p_m.m[ 2] + m[15]*p_m.m[ 3];

	mRet.m[ 4] = m[ 0]*p_m.m[ 4] + m[ 4]*p_m.m[ 5] + m[ 8]*p_m.m[ 6] + m[12]*p_m.m[ 7];
	mRet.m[ 5] = m[ 1]*p_m.m[ 4] + m[ 5]*p_m.m[ 5] + m[ 9]*p_m.m[ 6] + m[13]*p_m.m[ 7];
	mRet.m[ 6] = m[ 2]*p_m.m[ 4] + m[ 6]*p_m.m[ 5] + m[10]*p_m.m[ 6] + m[14]*p_m.m[ 7];
	mRet.m[ 7] = m[ 3]*p_m.m[ 4] + m[ 7]*p_m.m[ 5] + m[11]*p_m.m[ 6] + m[15]*p_m.m[ 7];

	mRet.m[ 8] = m[ 0]*p_m.m[ 8] + m[ 4]*p_m.m[ 9] + m[ 8]*p_m.m[10] + m[12]*p_m.m[11];
	mRet.m[ 9] = m[ 1]*p_m.m[ 8] + m[ 5]*p_m.m[ 9] + m[ 9]*p_m.m[10] + m[13]*p_m.m[11];
	mRet.m[10] = m[ 2]*p_m.m[ 8] + m[ 6]*p_m.m[ 9] + m[10]*p_m.m[10] + m[14]*p_m.m[11];
	mRet.m[11] = m[ 3]*p_m.m[ 8] + m[ 7]*p_m.m[ 9] + m[11]*p_m.m[10] + m[15]*p_m.m[11];

	mRet.m[12] = m[ 0]*p_m.m[12] + m[ 4]*p_m.m[13] + m[ 8]*p_m.m[14] + m[12]*p_m.m[15];
	mRet.m[13] = m[ 1]*p_m.m[12] + m[ 5]*p_m.m[13] + m[ 9]*p_m.m[14] + m[13]*p_m.m[15];
	mRet.m[14] = m[ 2]*p_m.m[12] + m[ 6]*p_m.m[13] + m[10]*p_m.m[14] + m[14]*p_m.m[15];
	mRet.m[15] = m[ 3]*p_m.m[12] + m[ 7]*p_m.m[13] + m[11]*p_m.m[14] + m[15]*p_m.m[15];
#endif
	
	return mRet;
}


}
