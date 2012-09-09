//========================================================================
// Week 9 - POD Files
//
// Example 2 - Complex POD file (building)
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
#include "PVRTModelPOD.h"
#include "W_MaterialManager.h"
#include "W_Model.h"

static wolf::Model* g_pModel;

void InitExample3()
{
    glEnable(GL_DEPTH_TEST);
    
	g_pModel = new wolf::Model("data/week9/building/building.pod", "data/week9/building/");
}

void RenderExample3()
{
    static glm::vec3 s_vCamPos(0.0f, 2.0f, 10.0f);
    static float s_fRot = 0.0f;

    if( glfwGetKey( GLFW_KEY_DOWN ) == GLFW_PRESS )
		s_vCamPos.z += 1.0f;
	else if( glfwGetKey( GLFW_KEY_UP ) == GLFW_PRESS )
		s_vCamPos.z -= 1.0f;
    if( glfwGetKey( GLFW_KEY_LEFT ) == GLFW_PRESS )
		s_vCamPos.x -= 1.0f;
    if( glfwGetKey( GLFW_KEY_RIGHT ) == GLFW_PRESS )
		s_vCamPos.x += 1.0f;

    s_fRot += 1.0f;
    
	glm::mat4 mProj = glm::perspective(45.0f, 1280.0f / 720.0f, 0.1f, 1000.0f);
	glm::mat4 mView = glm::lookAt(s_vCamPos, s_vCamPos - glm::vec3(0.0f,0.0f,1.0f), glm::vec3(0.0f,1.0f,0.0f));
	glm::mat4 mWorld = glm::rotate(s_fRot, 0.0f, 1.0f, 0.0f);
	
	g_pModel->Render(mWorld,mView,mProj);
}


