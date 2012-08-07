//========================================================================
// Week 3 - Buffers and Attributes
//
// Example 3: Rendering a cube 
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

struct Vertex
{
	GLfloat x,y,z;
	GLubyte r,g,b,a;
};

static const Vertex cubeVertices[] = {
// Front
	{ -0.5f, -0.5f, 0.5f, 255, 0, 0, 255 },
	{ -0.5f,  0.5f, 0.5f, 255, 0, 0, 255 },
	{  0.5f,  0.5f, 0.5f, 255, 0, 0, 255 },
	{  0.5f,  0.5f, 0.5f, 255, 0, 0, 255 },
	{  0.5f, -0.5f, 0.5f, 255, 0, 0, 255 },
	{ -0.5f, -0.5f, 0.5f, 255, 0, 0, 255 },

	// Back
	{  0.5f,  0.5f,-0.5f, 128, 0, 0, 255 },
	{ -0.5f,  0.5f,-0.5f, 128, 0, 0, 255 },
	{ -0.5f, -0.5f,-0.5f, 128, 0, 0, 255 },
	{ -0.5f, -0.5f,-0.5f, 128, 0, 0, 255 },
	{  0.5f, -0.5f,-0.5f, 128, 0, 0, 255 },
	{  0.5f,  0.5f,-0.5f, 128, 0, 0, 255 },

	// Left
	{ -0.5f,  0.5f,-0.5f, 0, 255, 0, 255 },
	{ -0.5f,  0.5f, 0.5f, 0, 255, 0, 255 },
	{ -0.5f, -0.5f, 0.5f, 0, 255, 0, 255 },
	{ -0.5f, -0.5f, 0.5f, 0, 255, 0, 255 },
	{ -0.5f, -0.5f,-0.5f, 0, 255, 0, 255 },
	{ -0.5f,  0.5f,-0.5f, 0, 255, 0, 255 },

	// Right
	{  0.5f,  0.5f, 0.5f, 0, 128, 0, 255 },
	{  0.5f,  0.5f,-0.5f, 0, 128, 0, 255 },
	{  0.5f, -0.5f,-0.5f, 0, 128, 0, 255 },
	{  0.5f, -0.5f,-0.5f, 0, 128, 0, 255 },
	{  0.5f, -0.5f, 0.5f, 0, 128, 0, 255 },
	{  0.5f,  0.5f, 0.5f, 0, 128, 0, 255 },

	// Top
	{ -0.5f,  0.5f, 0.5f, 0, 0, 255, 255 },
	{ -0.5f,  0.5f,-0.5f, 0, 0, 255, 255 },
	{  0.5f,  0.5f,-0.5f, 0, 0, 255, 255 },
	{  0.5f,  0.5f,-0.5f, 0, 0, 255, 255 },
	{  0.5f,  0.5f, 0.5f, 0, 0, 255, 255 },
	{ -0.5f,  0.5f, 0.5f, 0, 0, 255, 255 },

	// Bottom
	{ -0.5f, -0.5f, 0.5f, 0, 0, 128, 255 },
	{  0.5f, -0.5f, 0.5f, 0, 0, 128, 255 },
	{  0.5f, -0.5f,-0.5f, 0, 0, 128, 255 },
	{  0.5f, -0.5f,-0.5f, 0, 0, 128, 255 },
	{ -0.5f, -0.5f,-0.5f, 0, 0, 128, 255 },
	{ -0.5f, -0.5f, 0.5f, 0, 0, 128, 255 },
};

static GLuint program = 0;
static GLuint vbo = 0;
static GLuint vao = 0;

void InitExample3()
{
    glEnable(GL_DEPTH_TEST);
    
    program = wolf::LoadShaders("data/week3/cube.vsh", "data/week3/cube.fsh");

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 6 * 3 * 2, cubeVertices, GL_STATIC_DRAW);
    
    // Set attribute pointers
	int iPosAttr = glGetAttribLocation(program, "a_position");
	int iColAttr = glGetAttribLocation(program, "a_color");

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(iPosAttr,					// Attribute location
						  3,						// Number of components
						  GL_FLOAT,					// Type of each component
						  GL_FALSE,					// Normalize?
						  sizeof(Vertex),			// Stride
						  0);						// Offset
    glEnableVertexAttribArray(iPosAttr);

    glVertexAttribPointer(iColAttr,					// Attribute location
						  4,						// Number of components
						  GL_UNSIGNED_BYTE,			// Type of each component
						  GL_TRUE,					// Normalize?
						  sizeof(Vertex),			// Stride
						  (void*) (sizeof(GLfloat) * 3));		// Offset
    glEnableVertexAttribArray(iColAttr);
}

void RenderExample3()
{
    // Use shader program.
    glUseProgram(program);
    
	static float s_fRotation = 0;
	math::Matrix4 mProj = math::Matrix4::PerspectiveMatrixRHS(DEG_TO_RAD(90.0f), 1280.0f / 720.0f, 0.1f, 1000.0f, false);
	math::Matrix4 mView = math::Matrix4::LookAtMatrixRHS(math::Vec3D(0,0,4.0f), math::Vec3D(0,0,0), math::Vec3D(0,1,0));
	math::Matrix4 mWorld = math::Matrix4::RotateYMatrix(s_fRotation);
	mWorld = mWorld * math::Matrix4::RotateXMatrix(s_fRotation);
	s_fRotation += DEG_TO_RAD(1.0f);

	glUniformMatrix4fv(glGetUniformLocation(program,"projection"), 1, GL_FALSE, (GLfloat*)&mProj);
	glUniformMatrix4fv(glGetUniformLocation(program,"view"), 1, GL_FALSE, (GLfloat*)&mView);
	glUniformMatrix4fv(glGetUniformLocation(program,"world"), 1, GL_FALSE, (GLfloat*)&mWorld);
    
	glBindVertexArray(vao);

    // Draw!
	glDrawArrays(GL_TRIANGLES, 0, 6 * 3 * 2);
}


