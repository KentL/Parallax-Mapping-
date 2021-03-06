//========================================================================
// Week 4 - Getting stuff on screen!
//
// Example 3: Orthographic Projection
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

static const GLfloat squareVertices[] = {
	100.0f, 100.0f,
	100.0f, 300.0f,
	300.0f, 300.0f,

	300.0f, 300.0f,
	300.0f, 100.0f,
	100.0f, 100.0f,

	100.0f+50, 100.0f,
	100.0f + 50, 300.0f,
	300.0f + 50, 300.0f,

	300.0f + 50, 300.0f + 50,
	300.0f + 50, 100.0f + 50,
	100.0f + 50, 100.0f + 50
};

static const GLubyte squareColors[] = {
	255,   0, 0, 122, //yellow
	255, 0, 0, 122, //green
	255, 0, 0, 122, //red
	
	255, 0, 0, 122, //blue
	255, 0, 0, 122, //magenta
	255, 0, 0, 122, //cyan
	
	255, 255, 0, 122, //yellow
	255, 255, 0, 122, //green
	255, 255, 0, 122, //red

	255, 255, 0, 122, //blue
	255, 255, 0, 122, //magenta
	255, 255, 0, 122, //cyan
};

static GLuint program = 0;
static GLuint vboVerts = 0;
static GLuint vboColors = 0;
static GLuint vao = 0;

void InitExample3()
{
    program = wolf::LoadShaders("data/week4/example3.vsh", "data/week4/example3.fsh");

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
	// Create VBO for vertices
    glGenBuffers(1, &vboVerts);
    glBindBuffer(GL_ARRAY_BUFFER, vboVerts);
    
    glBufferData(GL_ARRAY_BUFFER, // Vertex Data
                 2*8 * 6,  // The total size of the buffer, in bytes
                 squareVertices, // Pointer to the data to copy over to VRAM
                 GL_STATIC_DRAW); // Hint to the driver for how it’ll be used.

	//glEnable(GL_DEPTH_TEST);
	//glEnable(GL_BLEND);

	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Create VBO for colors
    glGenBuffers(1, &vboColors);
    glBindBuffer(GL_ARRAY_BUFFER, vboColors);
    
    glBufferData(GL_ARRAY_BUFFER, // Vertex Data
		2 * 4 * 6,  // The total size of the buffer, in bytes
                 squareColors, // Pointer to the data to copy over to VRAM
                 GL_STATIC_DRAW); // Hint to the driver for how it’ll be used.
    
    // Set attribute pointers
	int iPosAttr = glGetAttribLocation(program, "a_position");
	int iColAttr = glGetAttribLocation(program, "a_color");

	glBindBuffer(GL_ARRAY_BUFFER, vboVerts);
    glVertexAttribPointer(iPosAttr,	// Attribute location
						  2,		// Number of components
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

void RenderExample3()
{
    // Use shader program.
    glUseProgram(program);
    
    glm::mat4 mProj = glm::ortho(0.0f,1280.0f,720.0f,0.0f,0.0f,1000.0f);

	glUniformMatrix4fv(glGetUniformLocation(program,"projection"), 
					   1, GL_FALSE, glm::value_ptr(mProj));
	
    glBindVertexArray(vao);
    
    // Draw!
	glDrawArrays(GL_TRIANGLES, 0, 2 * 6);
}
