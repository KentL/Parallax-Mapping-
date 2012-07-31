//========================================================================
// Week 2 - Getting stuff on screen!
//
// Example 3: 3D Triangle
//========================================================================
#define GLFW_INCLUDE_GL3
#define GLFW_NO_GLU
#include <stdio.h>
#include <stdlib.h>
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

void InitExample4()
{
    program = wolf::LoadShaders("data/week2/example4.vsh", "data/week2/example4.fsh");

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
	glBindBuffer(GL_ARRAY_BUFFER, vboVerts);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, vboColors);
    glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, 0, 0);
    glEnableVertexAttribArray(1);
}

void RenderExample4()
{
    // Use shader program.
    glUseProgram(program);
    
	math::Matrix4 mProj = math::Matrix4::PerspectiveMatrixRHS(DEG_TO_RAD(90.0f), 1280.0f / 720.0f, 0.1f, 1000.0f, false);
	math::Matrix4 mView = math::Matrix4::LookAtMatrixRHS(math::Vec3D(0,0,4.0f), math::Vec3D(0,0,0), math::Vec3D(0,1,0));
	
	glUniformMatrix4fv(glGetUniformLocation(program,"projection"), 1, GL_FALSE, (GLfloat*)&mProj);
	glUniformMatrix4fv(glGetUniformLocation(program,"view"), 1, GL_FALSE, (GLfloat*)&mView);
	
    glBindVertexArray(vao);
    
    // Draw!
    glDrawArrays(GL_TRIANGLES, 0, 3);
}
