//========================================================================
// Week 2 - Transformations
//
// 2D Quad.
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
	-1280.0f, -720.0f,
	-1280.0f, 720.0f,
	1280.0f, 720.0f,

	1280.0f, 720.0f,
	1280.0f, -720.0f,
	-1280.0f, -720.0f,
};

static const GLubyte squareColors[] = {
	//All Green:
	/*0,   255, 0, 255, 
	0,   255, 0, 255,
	0,   255, 0, 255, 
	
	0,   255, 0, 255, 
	0,   255, 0, 255, 
	0,   255, 0, 255, */

	//Colorful
	255, 0, 0, 255, 
	0, 255, 0, 255, 
	55, 55, 255, 255,

	250, 30, 0, 255, 
	30, 25, 255, 255, 
	0, 255, 100, 255,

};

static GLuint program = 0;
static GLuint vboVerts = 0;
static GLuint vboColors = 0;
static GLuint vao = 0;

void InitExample2D()
{
    program = wolf::LoadShaders("data/week2/2d.vsh", "data/week2/2d.fsh");

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
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

static glm::mat4 mWorld;
static void TEST_MATRIX(float p_00, float p_01, float p_02,
				        float p_10, float p_11, float p_12, 
				        float p_20, float p_21, float p_22)
{
	mWorld[0][0] = p_00;
	mWorld[0][1] = p_01;
	mWorld[0][2] = p_02;
	mWorld[0][3] = 0.0f;

	mWorld[1][0] = p_10;
	mWorld[1][1] = p_11;
	mWorld[1][2] = p_12;
	mWorld[1][3] = 0.0f;

	mWorld[2][0] = 0.0f;
	mWorld[2][1] = 0.0f;
	mWorld[2][2] = 1.0f;
	mWorld[2][3] = 0.0f;

	mWorld[3][0] = p_20;
	mWorld[3][1] = p_21;
	mWorld[3][2] = 0.0f;
	mWorld[3][3] = p_22;
}

void RenderExample2D()
{
    // Use shader program.
    glUseProgram(program);
    
    glm::mat4 mProj = glm::ortho(0.0f,1280.0f,0.0f,720.0f,0.0f,1000.0f);

	glUniformMatrix4fv(glGetUniformLocation(program,"projection"), 
					   1, GL_FALSE, glm::value_ptr(mProj));




	// CHANGE HERE
	TEST_MATRIX(1.0f, 0.0f, 0.0f,
				0.0f, 1.0f, 0.0f,
			    0.0f, 0.0f, 1.0f);
	// END CHANGE HERE

    



	glUniformMatrix4fv(glGetUniformLocation(program,"world"), 
					   1, GL_FALSE, glm::value_ptr(mWorld));
	
    glBindVertexArray(vao);
    
    // Draw!
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

