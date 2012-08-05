//========================================================================
// Week 2 - Getting stuff on screen!
//
// Example 3: Spinning 3D Triangle
//========================================================================
#define GLFW_INCLUDE_GL3
#define GLFW_NO_GLU
#include <stdio.h>
#include <stdlib.h>
#ifndef __APPLE__
#include <GL/glew.h>
#endif
#include <GL/glfw.h>
#include "W_Common.h"
#include "W_Math.h"

static const GLfloat triangleVertices[] = {
	-1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
};

static const GLubyte triangleColors[] = {
	255,   255, 0, 255, //yellow
	0,     255, 0, 255, //green
	255,     0, 0, 255, //red
};

static GLuint program = 0;
static GLuint vboVerts = 0;
static GLuint vboColors = 0;
static GLuint vao = 0;

void InitExample5()
{
    program = wolf::LoadShaders("data/week2/example5.vsh", "data/week2/example5.fsh");

	// Create VBO for vertices
    glGenBuffers(1, &vboVerts);
    glBindBuffer(GL_ARRAY_BUFFER, vboVerts);
    
    glBufferData(GL_ARRAY_BUFFER, // Vertex Data
                 12 * 3,  // The total size of the buffer, in bytes
                 triangleVertices, // Pointer to the data to copy over to VRAM
                 GL_STATIC_DRAW); // Hint to the driver for how it’ll be used.

	// Create VBO for colors
    glGenBuffers(1, &vboColors);
    glBindBuffer(GL_ARRAY_BUFFER, vboColors);
    
    glBufferData(GL_ARRAY_BUFFER, // Vertex Data
                 4 * 3,  // The total size of the buffer, in bytes
                 triangleColors, // Pointer to the data to copy over to VRAM
                 GL_STATIC_DRAW); // Hint to the driver for how it’ll be used.
    
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
    // Set attribute pointers
	int iPosAttr = glGetAttribLocation(program, "a_position");
	int iColAttr = glGetAttribLocation(program, "a_color");

	glBindBuffer(GL_ARRAY_BUFFER, vboVerts);
    glVertexAttribPointer(iPosAttr,	// Attribute location
						  3,		// Number of components
						  GL_FLOAT, // Type of each component
						  GL_FALSE, // Normalize?
						  0,		// Stride
						  0);		// Offset
    glEnableVertexAttribArray(iPosAttr);

	glBindBuffer(GL_ARRAY_BUFFER, vboColors);
    glVertexAttribPointer(iColAttr,			// Attribute location
						  4,				// Number of components
						  GL_UNSIGNED_BYTE, // Type of each component
						  GL_TRUE,			// Normalize?
						  0,				// Stride
						  0);				// Offset
    glEnableVertexAttribArray(iColAttr);
}

void RenderExample5()
{
    // Use shader program.
    glUseProgram(program);
    
	static float s_fRot = 0;

	math::Matrix4 mProj = math::Matrix4::PerspectiveMatrixRHS(DEG_TO_RAD(90.0f), 1280.0f / 720.0f, 0.1f, 1000.0f, false);
	math::Matrix4 mView = math::Matrix4::LookAtMatrixRHS(math::Vec3D(0,0,4.0f), math::Vec3D(0,0,0), math::Vec3D(0,1,0));
	math::Matrix4 mWorld = math::Matrix4::RotateYMatrix(s_fRot);

	s_fRot += DEG_TO_RAD(1.0f);
	
	
	glUniformMatrix4fv(glGetUniformLocation(program,"projection"), 1, GL_FALSE, (GLfloat*)&mProj);
	glUniformMatrix4fv(glGetUniformLocation(program,"view"), 1, GL_FALSE, (GLfloat*)&mView);
	glUniformMatrix4fv(glGetUniformLocation(program,"world"), 1, GL_FALSE, (GLfloat*)&mWorld);
	
    glBindVertexArray(vao);
    
    // Draw!
    glDrawArrays(GL_TRIANGLES, 0, 3);
}
