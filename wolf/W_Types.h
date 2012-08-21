//-----------------------------------------------------------------------------
// File:			W_Types.h
// Original Author:	Gordon Wood
//
// Common types throughout wolf (and some defines too)
//-----------------------------------------------------------------------------
#ifndef W_TYPES_H
#define W_TYPES_H

#define GLFW_INCLUDE_GL3
#define GLFW_NO_GLU
#ifndef __APPLE__
#include <GL/glew.h>
#endif
#include <GL/glfw.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace wolf
{

// Our attribute indices 
enum Attribute
{
	AT_Position = 0,
	AT_Color,
	AT_TexCoord1,
	AT_Normal,
	AT_Tangent,
	AT_NUM_ATTRIBS
};

enum ComponentType
{
	CT_Float = 0,
	CT_UByte,
	AT_NUM_COMPONENT_TYPES
};

struct Color4
{
	float r,g,b,a;

	Color4(float p_fR, float p_fG, float p_fB, float p_fA) : r(p_fR), g(p_fG), b(p_fB), a(p_fA) {}
};

#ifndef PI
#define PI		3.141592653589793238f
#endif
    
#define DEG_TO_RAD(d)  (((d)/180.0f)*PI)
    
}

#endif

