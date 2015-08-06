//========================================================================
// Week 2 - Transformations
//
// 3D Cube
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
	GLubyte r,g,b,a;
};

static const Vertex cubeVertices[] = {
	// Front
	{ -0.5f, -0.5f, 0.5f, 0, 0, 0, 255 },
	{ -0.5f,  0.5f, 0.5f, 0, 0, 0, 255 },
	{  0.5f,  0.5f, 0.5f, 0, 0, 0, 255 },
	{  0.5f,  0.5f, 0.5f, 0, 0, 0, 255 },
	{  0.5f, -0.5f, 0.5f, 0, 0, 0, 255 },
	{ -0.5f, -0.5f, 0.5f, 0, 0, 0, 255 },

	// Back
	{  0.5f,  0.5f,-0.5f, 128, 0, 0, 255 },
	{ -0.5f,  0.5f,-0.5f, 128, 0, 0, 255 },
	{ -0.5f, -0.5f,-0.5f, 128, 0, 0, 255 },
	{ -0.5f, -0.5f,-0.5f, 128, 0, 0, 255 },
	{  0.5f, -0.5f,-0.5f, 128, 0, 0, 255 },
	{  0.5f,  0.5f,-0.5f, 128, 0, 0, 255 },

	// Left
	{ -0.5f,  0.5f,-0.5f, 0, 255, 0, 255 },
	{ -0.5f,  0.5f, 0.5f, 0, 255, 0, 255 },
	{ -0.5f, -0.5f, 0.5f, 0, 255, 0, 255 },
	{ -0.5f, -0.5f, 0.5f, 0, 255, 0, 255 },
	{ -0.5f, -0.5f,-0.5f, 0, 255, 0, 255 },
	{ -0.5f,  0.5f,-0.5f, 0, 255, 0, 255 },

	// Right
	{  0.5f,  0.5f, 0.5f, 0, 128, 0, 255 },
	{  0.5f,  0.5f,-0.5f, 0, 128, 0, 255 },
	{  0.5f, -0.5f,-0.5f, 0, 128, 0, 255 },
	{  0.5f, -0.5f,-0.5f, 0, 128, 0, 255 },
	{  0.5f, -0.5f, 0.5f, 0, 128, 0, 255 },
	{  0.5f,  0.5f, 0.5f, 0, 128, 0, 255 },

	// Top
	{ -0.5f,  0.5f, 0.5f, 0, 0, 255, 255 },
	{ -0.5f,  0.5f,-0.5f, 0, 0, 255, 255 },
	{  0.5f,  0.5f,-0.5f, 0, 0, 255, 255 },
	{  0.5f,  0.5f,-0.5f, 0, 0, 255, 255 },
	{  0.5f,  0.5f, 0.5f, 0, 0, 255, 255 },
	{ -0.5f,  0.5f, 0.5f, 0, 0, 255, 255 },

	// Bottom
	{ -0.5f, -0.5f, 0.5f, 0, 0, 128, 255 },
	{  0.5f, -0.5f, 0.5f, 0, 0, 128, 255 },
	{  0.5f, -0.5f,-0.5f, 0, 0, 128, 255 },
	{  0.5f, -0.5f,-0.5f, 0, 0, 128, 255 },
	{ -0.5f, -0.5f,-0.5f, 0, 0, 128, 255 },
	{ -0.5f, -0.5f, 0.5f, 0, 0, 128, 255 },
};

static wolf::VertexBuffer* g_pVB = 0;
static wolf::VertexDeclaration* g_pDecl = 0;
static wolf::Program* g_pProgram = 0;
static wolf::Program* g_pAxesProgram = 0;

void InitExample3D()
{
    glEnable(GL_DEPTH_TEST);
    
    g_pAxesProgram = wolf::ProgramManager::CreateProgram("data/week2/3d_axes.vsh", "data/week2/3d_axes.fsh");
    g_pProgram = wolf::ProgramManager::CreateProgram("data/week2/3d.vsh", "data/week2/3d.fsh");
    g_pVB = wolf::BufferManager::CreateVertexBuffer(cubeVertices, sizeof(Vertex) * 6 * 3 * 2);

	g_pDecl = new wolf::VertexDeclaration();
	g_pDecl->Begin();
	g_pDecl->AppendAttribute(wolf::AT_Position, 3, wolf::CT_Float);
	g_pDecl->AppendAttribute(wolf::AT_Color, 4, wolf::CT_UByte);
	g_pDecl->SetVertexBuffer(g_pVB);
	g_pDecl->End();
}

static glm::mat4 mWorld;
static void TEST_MATRIX(float p_00, float p_01, float p_02, float p_03,
					    float p_10, float p_11, float p_12, float p_13,
				        float p_20, float p_21, float p_22, float p_23,
						float p_30, float p_31, float p_32, float p_33)
{
	mWorld[0][0] = p_00;
	mWorld[0][1] = p_01;
	mWorld[0][2] = p_02;
	mWorld[0][3] = p_03;

	mWorld[1][0] = p_10;
	mWorld[1][1] = p_11;
	mWorld[1][2] = p_12;
	mWorld[1][3] = p_13;

	mWorld[2][0] = p_20;
	mWorld[2][1] = p_21;
	mWorld[2][2] = p_22;
	mWorld[2][3] = p_23;

	mWorld[3][0] = p_30;
	mWorld[3][1] = p_31;
	mWorld[3][2] = p_32;
	mWorld[3][3] = p_33;
}

void RenderExample3D()
{
	static glm::vec3 s_vCamPos(1.0f,-1.0f,8.0f);
	glm::mat4 mProj = glm::perspective(45.0f, 1280.0f / 720.0f, 0.1f, 1000.0f);
	glm::mat4 mView = glm::lookAt(s_vCamPos, glm::vec3(0.0f,0.0f,0.0f), glm::vec3(0.0f,1.0f,0.0f));


    
    

	// CHANGE HERE
	TEST_MATRIX( 1.0f, 0.0f, 0.0f, 0.0f,
			     0.0f, 1.0f, 0.0f, 0.0f,
				 0.0f, 0.0f, 1.0f, 0.0f,
				 0.0f, 0.0f, 0.0f, 1.0f );
	// END CHANGE HERE





    if( glfwGetKey( GLFW_KEY_DOWN ) == GLFW_PRESS )
		s_vCamPos.y += 1.0f;
	else if( glfwGetKey( GLFW_KEY_UP ) == GLFW_PRESS )
		s_vCamPos.y -= 1.0f;
    if( glfwGetKey( GLFW_KEY_LEFT ) == GLFW_PRESS )
		s_vCamPos.x -= 1.0f;
    if( glfwGetKey( GLFW_KEY_RIGHT ) == GLFW_PRESS )
		s_vCamPos.x += 1.0f;
    if( glfwGetKey( GLFW_KEY_LSHIFT ) == GLFW_PRESS && glfwGetKey( GLFW_KEY_DOWN ) == GLFW_PRESS )
		s_vCamPos.z += 1.0f;
    if( glfwGetKey( GLFW_KEY_RSHIFT ) == GLFW_PRESS && glfwGetKey( GLFW_KEY_UP ) == GLFW_PRESS )
		s_vCamPos.z -= 1.0f;
    if( glfwGetKey( 'R' ) == GLFW_PRESS )
		s_vCamPos = glm::vec3(-3.0f,28.0f,14.0f);

    // Use shader program.
	g_pProgram->Bind();
    
	// Bind Uniforms
    g_pProgram->SetUniform("projection", mProj);
    g_pProgram->SetUniform("view", mView);
    g_pProgram->SetUniform("world", mWorld);    
    
	// Set up source data
	g_pDecl->Bind();

    // Draw!
	glDrawArrays(GL_TRIANGLES, 0, 6 * 3 * 2);

	// Draw axes
	{
		// Use shader program.
		g_pAxesProgram->Bind();

		// Bind Uniforms
		g_pAxesProgram->SetUniform("projection", mProj);
		g_pAxesProgram->SetUniform("view", mView);

		// Set up source data
		g_pDecl->Bind();

		// x-axis
		mWorld = glm::scale(1000.0f, 0.03f, 0.03f);
		g_pAxesProgram->SetUniform("world", mWorld);    
		glDrawArrays(GL_LINES, 0, 6 * 3 * 2);

		// y-axis
		mWorld = glm::scale(0.03f, 100.0f, 0.03f);
		g_pAxesProgram->SetUniform("world", mWorld);    
		glDrawArrays(GL_LINES, 0, 6 * 3 * 2);

		// z-axis
		mWorld = glm::scale(0.03f, 0.03f, 1000.0f);
		g_pAxesProgram->SetUniform("world", mWorld);    
		glDrawArrays(GL_LINES, 0, 6 * 3 * 2);
	}
}



