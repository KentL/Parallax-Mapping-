//========================================================================
// Week 8 - Pixel Tests and Blending
//
// Example 3: Blending
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
#include "W_TextureManager.h"

struct Vertex
{
	GLfloat x,y,z;
	GLfloat u,v;
};

static const Vertex cubeVertices[] = {
// Front
	{ -0.5f, -0.5f, 0.5f,		0.0f, 0.0f },
	{ -0.5f,  0.5f, 0.5f,		0.0f, 1.0f },
	{  0.5f,  0.5f, 0.5f,		1.0f, 1.0f },
	{  0.5f,  0.5f, 0.5f,		1.0f, 1.0f },
	{  0.5f, -0.5f, 0.5f,		1.0f, 0.0f },
	{ -0.5f, -0.5f, 0.5f,		0.0f, 0.0f },

	// Back
	{  0.5f,  0.5f,-0.5f,		0.0f, 0.0f },
	{ -0.5f,  0.5f,-0.5f,		0.0f, 1.0f },
	{ -0.5f, -0.5f,-0.5f,		1.0f, 1.0f },
	{ -0.5f, -0.5f,-0.5f,		1.0f, 1.0f },
	{  0.5f, -0.5f,-0.5f,		1.0f, 0.0f },
	{  0.5f,  0.5f,-0.5f,		0.0f, 0.0f },

	// Left
	{ -0.5f,  0.5f,-0.5f,		0.0f, 0.0f },
	{ -0.5f,  0.5f, 0.5f,		0.0f, 1.0f },
	{ -0.5f, -0.5f, 0.5f,		1.0f, 1.0f },
	{ -0.5f, -0.5f, 0.5f,		1.0f, 1.0f },
	{ -0.5f, -0.5f,-0.5f,		1.0f, 0.0f },
	{ -0.5f,  0.5f,-0.5f,		0.0f, 0.0f },

	// Right
	{  0.5f,  0.5f, 0.5f,		0.0f, 0.0f },
	{  0.5f,  0.5f,-0.5f,		0.0f, 1.0f },
	{  0.5f, -0.5f,-0.5f,		1.0f, 1.0f },
	{  0.5f, -0.5f,-0.5f,		1.0f, 1.0f },
	{  0.5f, -0.5f, 0.5f,		1.0f, 0.0f },
	{  0.5f,  0.5f, 0.5f,		0.0f, 0.0f },

	// Top
	{ -0.5f,  0.5f, 0.5f,		0.0f, 0.0f },
	{ -0.5f,  0.5f,-0.5f,		0.0f, 1.0f },
	{  0.5f,  0.5f,-0.5f,		1.0f, 1.0f },
	{  0.5f,  0.5f,-0.5f,		1.0f, 1.0f },
	{  0.5f,  0.5f, 0.5f,		1.0f, 0.0f },
	{ -0.5f,  0.5f, 0.5f,		0.0f, 0.0f },

	// Bottom
	{ -0.5f, -0.5f, 0.5f,		0.0f, 0.0f },
	{  0.5f, -0.5f, 0.5f,		0.0f, 1.0f },
	{  0.5f, -0.5f,-0.5f,		1.0f, 1.0f },
	{  0.5f, -0.5f,-0.5f,		1.0f, 1.0f },
	{ -0.5f, -0.5f,-0.5f,		1.0f, 0.0f },
	{ -0.5f, -0.5f, 0.5f,		0.0f, 0.0f },
};

static GLenum gs_aBlendModeMap[] =
{
	GL_SRC_ALPHA,				//BM_SrcAlpha,		
	GL_ONE,						//BM_One,				
	GL_SRC_COLOR,				//BM_SrcColor,
	GL_ONE_MINUS_SRC_COLOR,		//BM_OneMinusSrcColor,	
	GL_ONE_MINUS_SRC_ALPHA,		//BM_OneMinusSrcAlpha,
	GL_DST_ALPHA,				//BM_DstAlpha,			
	GL_ONE_MINUS_DST_ALPHA,		//BM_OneMinusDstAlpha,
	GL_DST_COLOR,				//BM_DstColor,			
	GL_ONE_MINUS_DST_COLOR,		//BM_OneMinusDstColor,	
	GL_ZERO,					//BM_Zero,				
};

static const char* gs_aBlendStringMap[] =
{
	"GL_SRC_ALPHA",				//BM_SrcAlpha,		
	"GL_ONE",					//BM_One,				
	"GL_SRC_COLOR",				//BM_SrcColor,
	"GL_ONE_MINUS_SRC_COLOR",	//BM_OneMinusSrcColor,	
	"GL_ONE_MINUS_SRC_ALPHA",	//BM_OneMinusSrcAlpha,
	"GL_DST_ALPHA",				//BM_DstAlpha,			
	"GL_ONE_MINUS_DST_ALPHA",	//BM_OneMinusDstAlpha,
	"GL_DST_COLOR",				//BM_DstColor,			
	"GL_ONE_MINUS_DST_COLOR",	//BM_OneMinusDstColor,	
	"GL_ZERO",					//BM_Zero,				
};

static wolf::VertexBuffer* g_pVB = 0;
static wolf::VertexDeclaration* g_pDecl = 0;
static wolf::Program* g_pProgram = 0;
static wolf::Texture* g_pTexture = 0;
static wolf::BlendMode g_eSrcFactor = wolf::BM_SrcAlpha;
static wolf::BlendMode g_eDstFactor = wolf::BM_OneMinusSrcAlpha;

void InitExample3()
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    
    g_pProgram = wolf::ProgramManager::CreateProgram("data/week8/cube_blend.vsh", "data/week8/cube_blend.fsh");
    g_pVB = wolf::BufferManager::CreateVertexBuffer(cubeVertices, sizeof(Vertex) * 6 * 3 * 2);

	g_pDecl = new wolf::VertexDeclaration();
	g_pDecl->Begin();
	g_pDecl->AppendAttribute(wolf::AT_Position, 3, wolf::CT_Float);
	g_pDecl->AppendAttribute(wolf::AT_TexCoord1, 2, wolf::CT_Float);
	g_pDecl->SetVertexBuffer(g_pVB);
	g_pDecl->End();

	g_pTexture = wolf::TextureManager::CreateTexture("data/week8/brick.dds");
}

wolf::BlendMode ToggleBlendMode(wolf::BlendMode p_eMode, int p_iFactor)
{
	int iNewMode = (int)p_eMode + p_iFactor;

	while( iNewMode < 0 )
		iNewMode += wolf::BM_NUM_BLEND_MODES;

	while( iNewMode >= wolf::BM_NUM_BLEND_MODES )
		iNewMode -= wolf::BM_NUM_BLEND_MODES;

	return (wolf::BlendMode) iNewMode;
}

void RenderExample3()
{
	static float s_fRotation = 0;
	glm::mat4 mProj = glm::perspective(45.0f, 1280.0f / 720.0f, 0.1f, 1000.0f);
	glm::mat4 mView = glm::lookAt(glm::vec3(0.0f,0.0f,4.0f), glm::vec3(0.0f,0.0f,0.0f), glm::vec3(0.0f,1.0f,0.0f));
	glm::mat4 mWorld = glm::rotate(s_fRotation, 0.0f, 1.0f, 0.0f);
	mWorld = mWorld * glm::rotate(s_fRotation, 1.0f, 0.0f, 0.0f);
	s_fRotation += 1.0f;

	static bool s_bLeft_Down = false;
	static bool s_bRight_Down = false;
	static bool s_bUp_Down = false;
	static bool s_bDown_Down = false;

    if( glfwGetKey( GLFW_KEY_LEFT ) == GLFW_PRESS )
		s_bLeft_Down = true;
	else if( s_bLeft_Down )
	{
		s_bLeft_Down = false;
		g_eSrcFactor = ToggleBlendMode(g_eSrcFactor, -1);
	}

    if( glfwGetKey( GLFW_KEY_RIGHT ) == GLFW_PRESS )
		s_bRight_Down = true;
	else if( s_bRight_Down )
	{
		s_bRight_Down = false;
		g_eSrcFactor = ToggleBlendMode(g_eSrcFactor, 1);
	}

    if( glfwGetKey( GLFW_KEY_UP ) == GLFW_PRESS )
		s_bUp_Down = true;
	else if( s_bUp_Down )
	{
		s_bUp_Down = false;
		g_eDstFactor = ToggleBlendMode(g_eDstFactor, -1);
	}

    if( glfwGetKey( GLFW_KEY_DOWN ) == GLFW_PRESS )
		s_bDown_Down = true;
	else if( s_bDown_Down )
	{
		s_bDown_Down = false;
		g_eDstFactor = ToggleBlendMode(g_eDstFactor, 1);
	}

	glBlendFunc(gs_aBlendModeMap[g_eSrcFactor], gs_aBlendModeMap[g_eDstFactor]);

	printf("Blend modes are...[%s\t%s]\n", gs_aBlendStringMap[g_eSrcFactor], gs_aBlendStringMap[g_eDstFactor]);

    // Use shader program.
	g_pProgram->Bind();
    
	g_pTexture->Bind();

	// Bind Uniforms
    g_pProgram->SetUniform("projection", mProj);
    g_pProgram->SetUniform("view", mView);
    g_pProgram->SetUniform("world", mWorld);    
    g_pProgram->SetUniform("texture", 0);    
    g_pProgram->SetUniform("fade", 0.5f);    
    
	// Set up source data
	g_pDecl->Bind();

    // Draw!
	glDrawArrays(GL_TRIANGLES, 0, 6 * 3 * 2);
}



