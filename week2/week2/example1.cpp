//========================================================================
// Week 2 - Getting stuff on screen!
//
// Example 1: Full-screen quad with no transformations necessary
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

static GLuint program = 0;
static GLuint vbo = 0;
static GLuint vao = 0;

void InitExample1()
{
    program = wolf::LoadShaders("data/week2/example1.vsh", "data/week2/example1.fsh");
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    
    glBufferData(GL_ARRAY_BUFFER, // Vertex Data
                 8 * 6,  // The total size of the buffer, in bytes
                 squareVertices, // Pointer to the data to copy over to VRAM
                 GL_STATIC_DRAW); // Hint to the driver for how it’ll be used.
    
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
    // Set attribute pointers
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);
}

void RenderExample1()
{
    // Use shader program.
    glUseProgram(program);
    
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBindVertexArray(vao);
    
    // Draw!
    glDrawArrays(GL_TRIANGLES, 0, 6);
}
