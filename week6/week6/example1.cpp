//========================================================================
// Week 6 - Textures Part 1
//
// Example 1: Simple texture
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
#include "W_BufferManager.h"
#include "W_VertexDeclaration.h"
#include "W_ProgramManager.h"

struct Vertex
{
	GLfloat x,y;
	GLfloat u,v;
};

static const Vertex squareVertices[] = {
	{ 100.0f, 100.0f,	0, 1 }, 
	{ 100.0f, 300.0f,	0, 0 }, 
	{ 300.0f, 300.0f,	1, 0 }, 

	{ 300.0f, 300.0f,	1, 0 }, 
	{ 300.0f, 100.0f,	1, 1 }, 
	{ 100.0f, 100.0,	0, 1 }, 
};

static GLubyte g_aTexture[] = {
     0, 0, 255,  // blue
     255, 255, 0, // yellow
     255, 0, 0,  // red
     0, 255, 0,  // green
//    255,0,0
};

static wolf::VertexBuffer* g_pVB = 0;
static wolf::VertexDeclaration* g_pDecl = 0;
static wolf::Program* g_pProgram = 0;
static GLuint tex;

void InitExample1()
{
    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
    
    g_pProgram = wolf::ProgramManager::CreateProgram("data/week6/one_texture.vsh", "data/week6/one_texture.fsh");
    g_pVB = wolf::BufferManager::CreateVertexBuffer(squareVertices, sizeof(Vertex) * 6);

	g_pDecl = new wolf::VertexDeclaration();
	g_pDecl->Begin();
	g_pDecl->AppendAttribute(wolf::AT_Position, 2, wolf::CT_Float);
	g_pDecl->AppendAttribute(wolf::AT_TexCoord1, 2, wolf::CT_Float);
	g_pDecl->SetVertexBuffer(g_pVB);
	g_pDecl->End();

	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 2, 2, 0,	GL_RGB, GL_UNSIGNED_BYTE, g_aTexture);
	// These two lines are explained soon!
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

void RenderExample1()
{
    glm::mat4 mProj = glm::ortho(0.0f,1280.0f,720.0f,0.0f,0.0f,1000.0f);

    // Use shader program.
	g_pProgram->Bind();
    
	// Bind Uniforms
    g_pProgram->SetUniform("projection", mProj);
    g_pProgram->SetUniform("tex", 0);
    
	// Set up source data
	g_pDecl->Bind();

    // Draw!
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

