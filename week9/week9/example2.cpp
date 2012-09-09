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

static CPVRTModelPOD g_pod;
static std::vector<wolf::VertexBuffer*> g_lVBs;
static std::vector<wolf::IndexBuffer*> g_lIBs;
static std::vector<wolf::VertexDeclaration*> g_lDecls;
static std::map<std::string,wolf::Material*> g_materials;

void InitExample2()
{
    glEnable(GL_DEPTH_TEST);
    
	// Load in the POD file
	g_pod.ReadFromFile("data/week9/building/building.pod");

	// Create all the mesh definitions
	for(int i = 0; i < g_pod.nNumMesh; i++)
	{
		SPODMesh* pMesh = &g_pod.pMesh[i];

		// Create the vertex buffer
		wolf::VertexBuffer* pVB = wolf::BufferManager::CreateVertexBuffer(pMesh->pInterleaved, pMesh->nNumVertex * pMesh->sVertex.nStride);

		// Create the index buffer
		wolf::IndexBuffer* pIB = wolf::BufferManager::CreateIndexBuffer(pMesh->nNumFaces*3);
		pIB->Write(pMesh->sFaces.pData);

		// Create the vertex declaration
		wolf::VertexDeclaration* pDecl = new wolf::VertexDeclaration;
		pDecl->Begin();
		pDecl->AppendAttribute(wolf::AT_Position, pMesh->sVertex.n, wolf::CT_Float);
		pDecl->AppendAttribute(wolf::AT_Normal, pMesh->sNormals.n, wolf::CT_Float);
		pDecl->AppendAttribute(wolf::AT_TexCoord1, pMesh->psUVW[0].n, wolf::CT_Float);
		pDecl->SetVertexBuffer(pVB);
		pDecl->SetIndexBuffer(pIB);
		pDecl->End();
    
		// Add them to our global list of them
		g_lVBs.push_back(pVB);
		g_lIBs.push_back(pIB);
		g_lDecls.push_back(pDecl);
	}

	// Now construct a map of all the used materials "converted" to wolf
	// Materials that we can use
	for(int i = 0; i < g_pod.nNumMeshNode; i++)
	{
        SPODNode* pNode = &g_pod.pNode[i];
		SPODMaterial* pPODMat = &g_pod.pMaterial[pNode->nIdxMaterial];
        
		// Check to see if the material has already been created
		std::map<std::string, wolf::Material*>::iterator iter = g_materials.find(pPODMat->pszName);

		if( iter == g_materials.end() )
		{
			// Not been created yet, so add it
            wolf::Material* pMat = wolf::MaterialManager::CreateMaterial(pPODMat->pszName);
			pMat->SetProgram("data/week9/textured.vsh", "data/week9/textured.fsh");

			// Grab the texture it's using and change the filename it expects to
			// be our TGA converted files, in the right path
            SPODTexture* pPODTex = &g_pod.pTexture[pPODMat->nIdxTexDiffuse];
            
            std::string strFilename = pPODTex->pszName;
            if( strFilename.find(".jpg") != std::string::npos )
                strFilename = strFilename.substr(0,strFilename.find(".jpg")) + std::string(".tga");
            else if( strFilename.find(".png") != std::string::npos )
                strFilename = strFilename.substr(0,strFilename.find(".png")) + std::string(".tga");

            strFilename = std::string("data/week9/building/") + strFilename;

			// Create the texture, make sure it's set to repeat, and assign it
			// to the material
			wolf::Texture* pTex = wolf::TextureManager::CreateTexture(strFilename.c_str());
			pTex->SetWrapMode(wolf::Texture::WM_Repeat,wolf::Texture::WM_Repeat);
			pMat->SetTexture("texture",pTex);

			// Add it to our global map of materials
			g_materials.insert( std::pair<std::string, wolf::Material*>(pPODMat->pszName, pMat));
		}
	}
}

void RenderExample2()
{
	static glm::vec3 s_vCamPos(0.0f, 2.0f, 10.0f);
    
    if( glfwGetKey( GLFW_KEY_DOWN ) == GLFW_PRESS )
		s_vCamPos.z += 1.0f;
	else if( glfwGetKey( GLFW_KEY_UP ) == GLFW_PRESS )
		s_vCamPos.z -= 1.0f;
    if( glfwGetKey( GLFW_KEY_LEFT ) == GLFW_PRESS )
		s_vCamPos.x -= 1.0f;
    if( glfwGetKey( GLFW_KEY_RIGHT ) == GLFW_PRESS )
		s_vCamPos.x += 1.0f;

	glm::mat4 mProj = glm::perspective(45.0f, 1280.0f / 720.0f, 0.1f, 1000.0f);
	glm::mat4 mView = glm::lookAt(s_vCamPos, s_vCamPos - glm::vec3(0.0f,0.0f,1.0f), glm::vec3(0.0f,1.0f,0.0f));
	glm::mat4 mWorld = glm::rotate(270.0f, 1.0f, 0.0f, 0.0f);

    static float s_fRot = 0.0f;
	s_fRot += 1.0f;
    
	// Go through every mesh node
	for(int i = 0; i < g_pod.nNumMeshNode; i++)
	{
        SPODNode* pNode = &g_pod.pNode[i];
        
		// Safeguard
        if( pNode->nIdx == -1 )
            continue;
        
		// Get the name of the material this node uses
		const char* strMat = g_pod.pMaterial[pNode->nIdxMaterial].pszName;

		// Grab the material from our map of materials
		wolf::Material* pMat = g_materials[strMat];
		pMat->SetUniform("projection", mProj);
		pMat->SetUniform("view", mView);

		// Calculate its world matrix from the POD file, plus add a little
		// rotation so we can see it all easily
        g_pod.GetWorldMatrix(*((PVRTMATRIX*)glm::value_ptr(mWorld)), *pNode);
        
        mWorld = glm::rotate(s_fRot, 0.0f, 1.0f, 0.0f)*mWorld;
		pMat->SetUniform("world", mWorld);  

		// Apply the material
		pMat->Apply();

		// Bind the source data
		g_lDecls[pNode->nIdx]->Bind();

		// Draw it!
		glDrawElements(GL_TRIANGLES, g_lIBs[pNode->nIdx]->GetNumIndices(), GL_UNSIGNED_SHORT, 0);
	}
}


