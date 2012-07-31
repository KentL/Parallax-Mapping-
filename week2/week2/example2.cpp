//========================================================================
// Week 2 - Getting stuff on screen!
//
// Example 2: Adding colors!
//========================================================================
#define GLFW_INCLUDE_GL3
#define GLFW_NO_GLU
#include <stdio.h>
#include <stdlib.h>
#include <GL/glfw.h>
#include "W_Common.h"

static const GLfloat squareVertices[] = {
	-1.0f,  -1.0f,
	 1.0f,  -1.0f,
	-1.0f,   1.0f,
	
	-1.0f,   1.0f,
	 1.0f,  -1.0f,
	 1.0f,   1.0f,
};

static const GLubyte squareColors[] = {
	255,   255, 0, 255, //yellow
	0,     255, 0, 255, //green
	255,     0, 0, 255, //red
	
	0,     0, 255, 255, //blue
	255,   0, 255, 255, //magenta
	0,   255, 255, 255, //cyan
};

static GLuint program = 0;
static GLuint vboVerts = 0;
static GLuint vboColors = 0;
static GLuint vao = 0;

void InitExample2()
{
    program = wolf::LoadShaders("data/week2/example2.vsh", "data/week2/example2.fsh");

	// Create VBO for vertices
    glGenBuffers(1, &vboVerts);
    glBindBuffer(GL_ARRAY_BUFFER, vboVerts);
    
    glBufferData(GL_ARRAY_BUFFER, // Vertex Data
                 8 * 6,  // The total size of the buffer, in bytes
                 squareVertices, // Pointer to the data to copy over to VRAM
                 GL_STATIC_DRAW); // Hint to the driver for how it’ll be used.

	// Create VBO for colors
    glGenBuffers(1, &vboColors);
    glBindBuffer(GL_ARRAY_BUFFER, vboColors);
    
    glBufferData(GL_ARRAY_BUFFER, // Vertex Data
                 4 * 6,  // The total size of the buffer, in bytes
                 squareColors, // Pointer to the data to copy over to VRAM
                 GL_STATIC_DRAW); // Hint to the driver for how it’ll be used.
    
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
    // Set attribute pointers
	glBindBuffer(GL_ARRAY_BUFFER, vboVerts);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, vboColors);
    glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, 0, 0);
    glEnableVertexAttribArray(1);
}

void RenderExample2()
{
    // Use shader program.
    glUseProgram(program);
    
    glBindVertexArray(vao);
    
    // Draw!
    glDrawArrays(GL_TRIANGLES, 0, 6);
}
