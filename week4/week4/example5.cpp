//========================================================================
// Week 4 - Getting stuff on screen!
//
// Example 5: Spinning 3D Triangle
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

static const GLfloat triangleVertices1[] = {
	
	0.0f, 1.0f, 0.0f,
	1.0f, 1.0f, 0.0f,
	1.0f, 1.0f, -1.0f,

	0.0f, 1.0f, 0.0f,
	0.0f, 1.0f, -1.0f,
	1.0f, 1.0f, -1.0f,//top

	1.0f, 1.0f, 0.0f,
	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, -1.0f,

	1.0f, 1.0f, 0.0f,
	1.0f, 0.0f, -1.0f,
	1.0f, 1.0f, -1.0f,//RIGHT


	0.0f, 1.0f, -1.0f,
	1.0f, 0.0f, -1.0f,
	1.0f, 1.0f, -1.0f,

	0.0f, 0.0f, -1.0f,
	1.0f, 0.0f, -1.0f,
	0.0f, 1.0f, -1.0f,//BACK

	0.0f, 0.0f, 0.0f,
	0.0f, 0.0f, -1.0f,
	0.0f, 1.0f, 0.0f,

	0.0f, 1.0f, 0.0f,
	0.0f, 0.0f, -1.0f,
	0.0f, 1.0f, -1.0f,//LEFT

	0.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,
	1.0f, 1.0f, 0.0f,

	0.0f, 0.0f, 0.0f,
	1.0f, 1.0f, 0.0f,
	0.0f, 1.0f, 0.0f,//FRONT

	0.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,
	0.0f, 0.0f, -1.0f,

	0.0f, 0.0f, -1.0f,
	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, -1.0f,//bottom


	
};

static const GLubyte triangleColors[] = {
	
	255, 0, 0, 255, //yellow
	255, 0, 0, 255, //green
	255, 0, 0, 255, //red

	255, 0, 0, 255, //yellow
	255, 0, 0, 255, //green
	255, 0, 0, 255, //red

	0, 255,0, 255, //yellow
	0, 255, 0, 255, //yellow
	0, 255, 0, 255, //yellow

	0, 255, 0, 255, //yellow
	0, 255, 0, 255, //yellow
	0, 255, 0, 255, //yellow

	0,  0,255, 255, //yellow
	0, 0, 255, 255, //yellow
	0, 0, 255, 255, //yellow

	0, 0, 255, 255, //yellow
	0, 0, 255, 255, //yellow
	0, 0, 255, 255, //yellow

	255, 0, 255, 255,
	255, 0, 255, 255,
	255, 0, 255, 255,

	255, 0, 255, 255,
	255, 0, 255, 255,
	255, 0, 255, 255,

	255,255,255,255,
	255, 255, 255, 255,
	255, 255, 255, 255,

	255, 255, 255, 255,
	255, 255, 255, 255,
	255, 255, 255, 255,

	255, 255, 0, 255,
	255, 255, 0, 255,
	255, 255, 0, 255,

	255, 255, 0, 255,
	255, 255, 0, 255,
	255, 255, 0, 255,



	
};



static GLuint program = 0;
static GLuint vboVerts = 0;
static GLuint vboColors = 0;
static GLuint vao = 0;

void InitExample5()
{

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	

    program = wolf::LoadShaders("data/week4/example5.vsh", "data/week4/example5.fsh");

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
	// Create VBO for vertices
    glGenBuffers(1, &vboVerts);
    glBindBuffer(GL_ARRAY_BUFFER, vboVerts);
    
    glBufferData(GL_ARRAY_BUFFER, // Vertex Data
                 12 * 16*3,  // The total size of the buffer, in bytes
                 triangleVertices1, // Pointer to the data to copy over to VRAM
                 GL_STATIC_DRAW); // Hint to the driver for how it’ll be used.
	

	// Create VBO for colors
    glGenBuffers(1, &vboColors);
    glBindBuffer(GL_ARRAY_BUFFER, vboColors);
    
    glBufferData(GL_ARRAY_BUFFER, // Vertex Data
                 4 * 36,  // The total size of the buffer, in bytes
                 triangleColors, // Pointer to the data to copy over to VRAM
                 GL_STATIC_DRAW); // Hint to the driver for how it’ll be used.

    
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

	glm::mat4 mProj = glm::perspective(90.0f, 1280.0f / 720.0f, 0.1f, 1000.0f);
	glm::mat4 mView = glm::lookAt(glm::vec3(0.0f,-0.0f,2.0f), glm::vec3(0.0f,0.0f,0.0f), glm::vec3(0.0f,1.0f,0.0f));
	glm::mat4 mRot1 = glm::rotate(s_fRot, 0.0f, 1.0f, 0.0f);
	glm::mat4 mRot2 = glm::rotate(s_fRot, 0.0f, 1.0f, 0.0f);
	glm::mat4 mRot3 = glm::rotate(s_fRot, 1.0f, 0.0f, 0.0f);
	glm::mat4 mRot4 = glm::rotate(45.0f, 0.0f, 1.0f, 0.0f);
	glm::mat4 mRot5 = glm::rotate(45.0f, 1.0f, 0.0f, 0.0f);
	s_fRot += 1.0f;
	
    glBindVertexArray(vao);
	
	glm::mat4 mWorldViewProj1 = mProj * mView*glm::translate(-2.0f, 0.0f, 0.0f);// *mRot4;// *mRot5;
	glUniformMatrix4fv(glGetUniformLocation(program, "WorldViewProj"), 1, GL_FALSE, glm::value_ptr(mWorldViewProj1));
	glDrawArrays(GL_TRIANGLES, 0, 36);

	mWorldViewProj1 = mProj * mView * mRot2;// mRot4;// *mRot5;
	glUniformMatrix4fv(glGetUniformLocation(program, "WorldViewProj"), 1, GL_FALSE, glm::value_ptr(mWorldViewProj1));
	glDrawArrays(GL_TRIANGLES, 0, 36);

	mWorldViewProj1 = mProj * mView * glm::translate(2.0f, 0.0f, 0.0f)*mRot4 *mRot3;
	glUniformMatrix4fv(glGetUniformLocation(program, "WorldViewProj"), 1, GL_FALSE, glm::value_ptr(mWorldViewProj1));
	glDrawArrays(GL_TRIANGLES, 0, 36);

	

	

    
}
