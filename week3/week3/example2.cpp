//========================================================================
// Week 3 - Buffers and Attributes
//
// Example 2: Interleaved data and index buffers
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
	{ 1.0f,   1.0f,		0, 255, 255, 255 },
};

static const unsigned short squareIndices[] = {
	0,
	1,
	2,

	2,
	1,
	3,
};

namespace wolf
{
    class Program
    {
    public:
        Program(const char*,const char*) {}
    };
    class VertexBuffer
    {
    public:
        VertexBuffer(const void*,int) {}
    };
    class VertexDeclaration
    {
    public:
        VertexDeclaration() {}
        void SetVertexBuffer(VertexBuffer*) {}
        void AppendAttribute(Attribute,int,ComponentType) {}
    };
}
static wolf::Program* m_pShader;
static wolf::VertexBuffer* m_pQuadVB;
static wolf::VertexDeclaration* m_pQuadDecl;

static GLuint program = 0;
static GLuint vbo = 0;
static GLuint indexBuffer = 0;
static GLuint vao = 0;

void InitExample2()
{
    m_pShader = new wolf::Program("data/week3/cube.vsh","data/week3/cube.fsh");
    
    m_pQuadVB = new wolf::VertexBuffer(squareVertices, sizeof(Vertex) * 4);
    
    m_pQuadDecl = new wolf::VertexDeclaration();
    m_pQuadDecl->SetVertexBuffer(m_pQuadVB);
    m_pQuadDecl->AppendAttribute(wolf::AT_Position, 3, wolf::CT_Float);
    m_pQuadDecl->AppendAttribute(wolf::AT_Color, 4, wolf::CT_UByte);
    program = wolf::LoadShaders("data/week3/colored.vsh", "data/week3/colored.fsh");

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    
    glBufferData(GL_ARRAY_BUFFER, // Vertex Data
                 sizeof(Vertex) * 4,  // The total size of the buffer, in bytes
                 squareVertices, // Pointer to the data to copy over to VRAM
                 GL_STATIC_DRAW); // Hint to the driver for how it’ll be used.
    
    glGenBuffers(1, &indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, // Index Data
			     6 * sizeof(GLushort),	  // The total size of the buffer, in bytes
				 squareIndices,			  // Pointer to the data to copy over to VRAM
				 GL_STATIC_DRAW);		  // Hint to the driver for how it'll be used.

    // Set attribute pointers
	int iPosAttr = glGetAttribLocation(program, "a_position");
	int iColAttr = glGetAttribLocation(program, "a_color");

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
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

void RenderExample2()
{
    // Use shader program.
    glUseProgram(program);
    
	glBindVertexArray(vao);
    
    // Draw!
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
}

