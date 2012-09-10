//========================================================================
// Week 10 - Lighting Part 1
//
// Example 1: Diffuse lighting on cube
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
	GLfloat x,y,z;
	GLfloat nx, ny, nz;
};

static const Vertex g_aCubeVerts[] = 
{
	// Front
	{ -0.5f, -0.5f, 0.5f, 0, 0, 1 }, 
	{ -0.5f,  0.5f, 0.5f, 0, 0, 1 }, 
	{  0.5f,  0.5f, 0.5f, 0, 0, 1 }, 
	{  0.5f,  0.5f, 0.5f, 0, 0, 1 }, 
	{  0.5f, -0.5f, 0.5f, 0, 0, 1 }, 
	{ -0.5f, -0.5f, 0.5f, 0, 0, 1 }, 

	// Back
	{  0.5f,  0.5f,-0.5f, 0, 0, -1 },
	{ -0.5f,  0.5f,-0.5f, 0, 0, -1 },
	{ -0.5f, -0.5f,-0.5f, 0, 0, -1 },
	{ -0.5f, -0.5f,-0.5f, 0, 0, -1 },
	{  0.5f, -0.5f,-0.5f, 0, 0, -1 },
	{  0.5f,  0.5f,-0.5f, 0, 0, -1 },

	// Left
	{ -0.5f,  0.5f,-0.5f, -1, 0, 0 },
	{ -0.5f,  0.5f, 0.5f, -1, 0, 0 },
	{ -0.5f, -0.5f, 0.5f, -1, 0, 0 },
	{ -0.5f, -0.5f, 0.5f, -1, 0, 0 },
	{ -0.5f, -0.5f,-0.5f, -1, 0, 0 },
	{ -0.5f,  0.5f,-0.5f, -1, 0, 0 },

	// Right
	{  0.5f,  0.5f, 0.5f, 1, 0, 0 },
	{  0.5f,  0.5f,-0.5f, 1, 0, 0 },
	{  0.5f, -0.5f,-0.5f, 1, 0, 0 },
	{  0.5f, -0.5f,-0.5f, 1, 0, 0 },
	{  0.5f, -0.5f, 0.5f, 1, 0, 0 },
	{  0.5f,  0.5f, 0.5f, 1, 0, 0 },

	// Top
	{ -0.5f,  0.5f, 0.5f, 0, 1, 0 },
	{ -0.5f,  0.5f,-0.5f, 0, 1, 0 },
	{  0.5f,  0.5f,-0.5f, 0, 1, 0 },
	{  0.5f,  0.5f,-0.5f, 0, 1, 0 },
	{  0.5f,  0.5f, 0.5f, 0, 1, 0 },
	{ -0.5f,  0.5f, 0.5f, 0, 1, 0 },

	// Bottom
	{ -0.5f, -0.5f, 0.5f, 0, -1, 0 },
	{  0.5f, -0.5f, 0.5f, 0, -1, 0 },
	{  0.5f, -0.5f,-0.5f, 0, -1, 0 },
	{  0.5f, -0.5f,-0.5f, 0, -1, 0 },
	{ -0.5f, -0.5f,-0.5f, 0, -1, 0 },
	{ -0.5f, -0.5f, 0.5f, 0, -1, 0 },
};

static wolf::VertexBuffer* g_pVB = 0;
static wolf::VertexDeclaration* g_pDecl = 0;
static wolf::Program* g_pProgram = 0;

void InitExample1()
{
    glEnable(GL_DEPTH_TEST);
    
    g_pProgram = wolf::ProgramManager::CreateProgram("data/week10/example1.vsh", "data/week10/example1.fsh");
    g_pVB = wolf::BufferManager::CreateVertexBuffer(g_aCubeVerts, sizeof(Vertex) * 6 * 3 * 2);

	g_pDecl = new wolf::VertexDeclaration();
	g_pDecl->Begin();
	g_pDecl->AppendAttribute(wolf::AT_Position, 3, wolf::CT_Float);
	g_pDecl->AppendAttribute(wolf::AT_Normal, 3, wolf::CT_Float);
	g_pDecl->SetVertexBuffer(g_pVB);
	g_pDecl->End();
}

void RenderExample1()
{
	static float s_fRotation = 0;
	glm::mat4 mProj = glm::perspective(45.0f, 1280.0f / 720.0f, 0.1f, 1000.0f);
	glm::mat4 mView = glm::lookAt(glm::vec3(0.0f,0.0f,4.0f), glm::vec3(0.0f,0.0f,0.0f), glm::vec3(0.0f,1.0f,0.0f));
	glm::mat4 mWorld = glm::rotate(s_fRotation, 0.0f, 1.0f, 0.0f);
	mWorld = mWorld * glm::rotate(s_fRotation, 1.0f, 0.0f, 0.0f);
	s_fRotation += 1.0f;

    // Use shader program.
	g_pProgram->Bind();
    
	// Bind Uniforms
	glm::mat4 mWVP = mProj * mView * mWorld;
	glm::mat3 mWorldIT(mWorld);
	mWorldIT = glm::inverse(mWorldIT);
	mWorldIT = glm::transpose(mWorldIT);

    g_pProgram->SetUniform("WorldViewProj", mWVP);
	g_pProgram->SetUniform("WorldIT", mWorldIT);
    g_pProgram->SetUniform("LightDir", -glm::vec3(0.0f,0.0f,-1.0f));
    g_pProgram->SetUniform("LightColor", glm::vec4(1.0f,0.0f,0.0f,1.0f));
    
	// Set up source data
	g_pDecl->Bind();

    // Draw!
	glDrawArrays(GL_TRIANGLES, 0, 6 * 3 * 2);
}


