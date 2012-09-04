//========================================================================
// Week 8 - Pixel Tests and Blending
//
// Example 4: Material Class
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
#include "W_TextureManager.h"
#include "W_MaterialManager.h"

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

static wolf::VertexBuffer* g_pVB = 0;
static wolf::VertexDeclaration* g_pDecl = 0;
static wolf::Material* g_pLeftMat = 0;
static wolf::Material* g_pRightMat = 0;

void InitExample4()
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    
    g_pVB = wolf::BufferManager::CreateVertexBuffer(cubeVertices, sizeof(Vertex) * 6 * 3 * 2);

	g_pDecl = new wolf::VertexDeclaration();
	g_pDecl->Begin();
	g_pDecl->AppendAttribute(wolf::AT_Position, 3, wolf::CT_Float);
	g_pDecl->AppendAttribute(wolf::AT_TexCoord1, 2, wolf::CT_Float);
	g_pDecl->SetVertexBuffer(g_pVB);
	g_pDecl->End();

	g_pLeftMat = wolf::MaterialManager::CreateMaterial("Left");
	g_pLeftMat->SetProgram("data/week8/cube_tex.vsh", "data/week8/cube_tex.fsh");
    g_pLeftMat->SetUniform("fade", 0.5f);    
	g_pLeftMat->SetBlend(true);
	g_pLeftMat->SetBlendMode(wolf::BM_SrcAlpha, wolf::BM_OneMinusSrcAlpha);
	g_pLeftMat->SetTexture("texture", wolf::TextureManager::CreateTexture("data/week8/brick.dds"));

	g_pRightMat = wolf::MaterialManager::CreateMaterial("Right");
	g_pRightMat->SetProgram("data/week8/cube_tex.vsh", "data/week8/cube_tex.fsh");
    g_pRightMat->SetUniform("fade", 0.25f);    
	g_pRightMat->SetBlend(true);
	g_pRightMat->SetBlendMode(wolf::BM_SrcAlpha, wolf::BM_One);
	g_pRightMat->SetTexture("texture", wolf::TextureManager::CreateTexture("data/week7/metal.tga"));
}

void RenderExample4()
{
	static float s_fRotation = 0;
	glm::mat4 mProj = glm::perspective(45.0f, 1280.0f / 720.0f, 0.1f, 1000.0f);
	glm::mat4 mView = glm::lookAt(glm::vec3(0.0f,0.0f,4.0f), glm::vec3(0.0f,0.0f,0.0f), glm::vec3(0.0f,1.0f,0.0f));
	s_fRotation += 1.0f;

    // Use shader program.
	glm::mat4 mWorldLeft = glm::translate(-1.0f, 0.0f, 0.0f) * 
						   glm::rotate(s_fRotation, 0.0f, 1.0f, 0.0f) * 
						   glm::rotate(s_fRotation, 1.0f, 0.0f, 0.0f);

	glm::mat4 mWorldRight = glm::translate(1.0f, 0.0f, 0.0f) * 
						    glm::rotate(s_fRotation, 0.0f, 1.0f, 0.0f) * 
						    glm::rotate(s_fRotation, 1.0f, 0.0f, 0.0f);

	// Set up source data
	g_pDecl->Bind();

	// Bind Uniforms
    g_pLeftMat->SetUniform("projection", mProj);
    g_pLeftMat->SetUniform("view", mView);
    g_pLeftMat->SetUniform("world", mWorldLeft);    
	g_pLeftMat->Apply();
    
    // Draw!
	glDrawArrays(GL_TRIANGLES, 0, 6 * 3 * 2);

    g_pRightMat->SetUniform("projection", mProj);
    g_pRightMat->SetUniform("view", mView);
    g_pRightMat->SetUniform("world", mWorldRight);    
	g_pRightMat->Apply();
	glDrawArrays(GL_TRIANGLES, 0, 6 * 3 * 2);
}



