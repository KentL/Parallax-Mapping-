//========================================================================
// Week 10 - Lighting Part 1
//
// Example 3 - Specular lighting, per-vertex
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

static wolf::VertexBuffer* g_pVB = 0;
static wolf::IndexBuffer* g_pIB = 0;
static wolf::VertexDeclaration* g_pDecl = 0;
static wolf::Material* g_pMat = 0;
static bool g_bDepthOn = true;
static bool g_bDepthKeyDown = false;
 
void InitExample3()
{
    glEnable(GL_DEPTH_TEST);
    
    CPVRTModelPOD pod;
	pod.ReadFromFile("data/week9/test.pod");

    SPODMesh* pMesh = &pod.pMesh[0];
    g_pVB = wolf::BufferManager::CreateVertexBuffer(pMesh->pInterleaved, pMesh->nNumVertex * pMesh->sVertex.nStride);
    g_pIB = wolf::BufferManager::CreateIndexBuffer(pMesh->nNumFaces*3);
    g_pIB->Write(pMesh->sFaces.pData);
    
    g_pDecl = new wolf::VertexDeclaration;
    g_pDecl->Begin();
    g_pDecl->AppendAttribute(wolf::AT_Position, pMesh->sVertex.n, wolf::CT_Float);
    g_pDecl->AppendAttribute(wolf::AT_Normal, pMesh->sNormals.n, wolf::CT_Float);
    g_pDecl->AppendAttribute(wolf::AT_TexCoord1, pMesh->psUVW[0].n, wolf::CT_Float);
    g_pDecl->SetVertexBuffer(g_pVB);
    g_pDecl->SetIndexBuffer(g_pIB);
    g_pDecl->End();
    
    g_pMat = wolf::MaterialManager::CreateMaterial("myMat");
    g_pMat->SetProgram("data/week10/example3.vsh", "data/week10/example3.fsh");
	wolf::Texture* pTex = wolf::TextureManager::CreateTexture("data/week10/MaskMain.tga");
	pTex->SetWrapMode(wolf::Texture::WM_Repeat);
    g_pMat->SetTexture("texture", pTex);
}

void RenderExample3()
{
	glm::mat4 mProj = glm::perspective(45.0f, 1280.0f / 720.0f, 0.1f, 1000.0f);
	glm::mat4 mView = glm::lookAt(glm::vec3(0.0f,30.0f,60.0f), glm::vec3(0.0f,30.0f,0.0f), glm::vec3(0.0f,1.0f,0.0f));
	glm::mat4 mWorld = glm::rotate(0.0f, 0.0f, 1.0f, 0.0f);

	// Bind Uniforms
	glm::mat4 mWVP = mProj * mView * mWorld;
	glm::mat3 mWorldIT(mWorld);
	mWorldIT = glm::inverse(mWorldIT);
	mWorldIT = glm::transpose(mWorldIT);

    g_pMat->SetUniform("WorldViewProj", mWVP);
	g_pMat->SetUniform("WorldIT", mWorldIT);
    g_pMat->SetUniform("Light1Dir", -glm::vec3(0.0f,0.0f,-1.0f));
    g_pMat->SetUniform("Light1Color", glm::vec4(0.6f,0.6f,0.2f,1.0f));
    g_pMat->SetUniform("ViewDir", glm::vec3(0.0f,0.0f,1.0f));
	g_pMat->SetUniform("SpecularColor", glm::vec3(1.0f,1.0f,1.0f));
	g_pMat->SetUniform("Shininess", 200.0f);
    
	// Use shader program.
	g_pMat->Apply();
    
    
	// Set up source data
	g_pDecl->Bind();

    // Draw!
	glDrawElements(GL_TRIANGLES, g_pIB->GetNumIndices(), GL_UNSIGNED_SHORT, 0);
}


