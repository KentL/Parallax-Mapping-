//========================================================================
// Week 7 - Textures Part 2
//
// Example 4: RGBA 5551
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

#define TEX 1

#if TEX == 0

static GLushort g_aTexture[] =
{
	 0x003f,  // blue
     0xffc1, // yellow
     0xf801,  // red
     0x07c1,  // green
};

#else

static GLushort g_aTexture[32*32];

#endif


static wolf::VertexBuffer* g_pVB = 0;
static wolf::VertexDeclaration* g_pDecl = 0;
static wolf::Program* g_pProgram = 0;
static GLuint tex;

void InitExample4()
{
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    
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

#if TEX == 0
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 2, 2, 0,	GL_RGBA, GL_UNSIGNED_SHORT_5_5_5_1, g_aTexture);
#else
for( int v = 0; v < 32; v++ )
	{
		for( int u = 0; u < 32; u++ )
		{
			g_aTexture[v*32 + u] = 0x0001 | (v<<1);
		}
	}

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 32, 32, 0,	GL_RGBA, GL_UNSIGNED_SHORT_5_5_5_1, g_aTexture);
#endif

	// These two lines are explained soon!
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

void RenderExample4()
{
    glm::mat4 mProj = glm::ortho(0.0f,1280.0f,720.0f,0.0f,0.0f,1000.0f);

    // Use shader program.
	g_pProgram->Bind();
    
	// Bind Uniforms
	g_pProgram->SetUniform("projection", mProj);
    g_pProgram->SetUniform("texture", 0);
    
	// Set up source data
	g_pDecl->Bind();

    // Draw!
	glDrawArrays(GL_TRIANGLES, 0, 6);
}


