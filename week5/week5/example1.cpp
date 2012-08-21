//========================================================================
// Week 5 - Buffers and Attributes
//
// Example 1: Interleaved data
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

struct Vertex
{
	GLfloat x,y;
	GLubyte r,g,b,a;
};

static const Vertex squareVertices[] = {
	{ -1.0f,  -1.0f,	255, 255, 0, 255 },
	{ 1.0f,  -1.0f,		0, 255, 0, 255 },
	{ -1.0f,   1.0f,	255, 0, 0, 255 },
	
	{ -1.0f,   1.0f,	255, 0, 0, 255 },
	{ 1.0f,  -1.0f,		0, 255, 0, 255 },
	{ 1.0f,   1.0f,		0, 255, 255, 255 },
};

static GLuint program = 0;
static GLuint vboVerts = 0;
static GLuint vao = 0;

void InitExample1()
{
    program = wolf::LoadShaders("data/week5/colored.vsh", "data/week5/colored.fsh");

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
	// Create VBO for vertices
    glGenBuffers(1, &vboVerts);
    glBindBuffer(GL_ARRAY_BUFFER, vboVerts);
    
    glBufferData(GL_ARRAY_BUFFER, // Vertex Data
                 sizeof(Vertex) * 6,  // The total size of the buffer, in bytes
                 squareVertices, // Pointer to the data to copy over to VRAM
                 GL_STATIC_DRAW); // Hint to the driver for how it’ll be used.

    // Set attribute pointers
	int iPosAttr = glGetAttribLocation(program, "a_position");
	int iColAttr = glGetAttribLocation(program, "a_color");

	glBindBuffer(GL_ARRAY_BUFFER, vboVerts);
    glVertexAttribPointer(iPosAttr,					// Attribute location
						  2,						// Number of components
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
						  (void*) (sizeof(GLfloat) * 2));		// Offset
    glEnableVertexAttribArray(iColAttr);
}

void RenderExample1()
{
    // Use shader program.
    glUseProgram(program);
    
    glBindVertexArray(vao);
    
    // Draw!
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

