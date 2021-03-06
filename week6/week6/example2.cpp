//========================================================================
// Week 6 - Textures Part 1
//
// Example 2: Texture from tga file
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

static wolf::VertexBuffer* g_pVB = 0;
static wolf::VertexDeclaration* g_pDecl = 0;
static wolf::Program* g_pProgram = 0;
static GLuint tex;
static GLuint tex2;
static wolf::VertexBuffer* g_pVB2 = 0;
static wolf::VertexDeclaration* g_pDecl2 = 0;

void InitExample2()
{
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	g_pProgram = wolf::ProgramManager::CreateProgram("data/week6/one_texture.vsh", "data/week6/one_texture.fsh");
	g_pVB = wolf::BufferManager::CreateVertexBuffer(sizeof(Vertex) * 6);

	g_pDecl = new wolf::VertexDeclaration();
	g_pDecl->Begin();
	g_pDecl->AppendAttribute(wolf::AT_Position, 2, wolf::CT_Float);
	g_pDecl->AppendAttribute(wolf::AT_TexCoord1, 2, wolf::CT_Float);
	g_pDecl->SetVertexBuffer(g_pVB);
	g_pDecl->End();

	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);

	GLFWimage img;
	glfwReadImage("data/week6/brick.tga", &img, 0);
	glTexImage2D(GL_TEXTURE_2D, 0, img.Format, img.Width, img.Height, 0, img.Format, GL_UNSIGNED_BYTE, img.Data);
	glfwFreeImage(&img);

	// These two lines are explained soon!
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glGenTextures(1, &tex2);
	glBindTexture(GL_TEXTURE_2D, tex2);


	glfwReadImage("data/week6/color.tga", &img, 0);
	glTexImage2D(GL_TEXTURE_2D, 0, img.Format, img.Width, img.Height, 0, img.Format, GL_UNSIGNED_BYTE, img.Data);
	glfwFreeImage(&img);

	// These two lines are explained soon!
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, tex2);
	
}

void RenderExample2()
{
    glm::mat4 mProj = glm::ortho(0.0f,1280.0f,720.0f,0.0f,0.0f,1000.0f);
	g_pVB->Write(squareVertices);
    // Use shader program.
	g_pProgram->Bind();
    
	// Bind Uniforms
    g_pProgram->SetUniform("projection", mProj);
    g_pProgram->SetUniform("texture", 1);
    
	// Set up source data
	g_pDecl->Bind();

    // Draw!
	glDrawArrays(GL_TRIANGLES, 0, 6);
}


