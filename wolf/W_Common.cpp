//-----------------------------------------------------------------------------
// File:			W_Common.cpp
// Original Author:	Gordon Wood
//
// See header for notes
//-----------------------------------------------------------------------------
#include "W_Common.h"
#include "W_Types.h"

namespace wolf
{

//----------------------------------------------------------
// Loads in a whole file and returns the contents. User is 
// responsible for then delete[]-ing the data. Returns 0 if 
// file not able to be loaded.
//----------------------------------------------------------
void* LoadWholeFile(const std::string& p_strFile)
{
	FILE* fp = fopen(p_strFile.c_str(), "rb");
	if( !fp )
		return 0;

	fseek(fp, 0, SEEK_END);
	size_t len = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	char* pRet = new char[len+1];
	fread(pRet, sizeof(char), len, fp);
    pRet[len] = 0;
	fclose(fp);

	return pRet;
}

//----------------------------------------------------------
// Compiles a shader of the given type (GL_VERTEX_SHADER or
// GL_FRAGMENT_SHADER) from the given file and stores the 
// resulting shader object in p_pShader. Returns true on success,
// else false
//----------------------------------------------------------
bool CompileShader(GLuint* p_pShader, GLenum p_eType, const std::string& p_strFile)
{
    GLint iStatus;
    const GLchar* pSource;
    
    pSource = (GLchar *) LoadWholeFile(p_strFile);
    if( !pSource )
    {
        printf("Failed to load vertex shader\n");
        return false;
    }
    
    *p_pShader = glCreateShader(p_eType);
    glShaderSource(*p_pShader, 1, &pSource, NULL);
    glCompileShader(*p_pShader);
    
#if defined(DEBUG)
    GLint iLogLength;
    glGetShaderiv(*p_pShader, GL_INFO_LOG_LENGTH, &iLogLength);
    if( iLogLength > 0 )
    {
        GLchar* pLog = (GLchar *)malloc(iLogLength);
        glGetShaderInfoLog(*p_pShader, iLogLength, &iLogLength, pLog);
        printf("Shader compile log:\n%s\n", pLog);
        free(pLog);
    }
#endif
    
    glGetShaderiv(*p_pShader, GL_COMPILE_STATUS, &iStatus);
    if( iStatus == 0 )
    {
        glDeleteShader(*p_pShader);
        return false;
    }
    
    return true;
}

//----------------------------------------------------------
// Performs the linking stage of the vertex and pixel shader,
// resulting in a final program object to use. Checks for
// errors and prints them and returns true on success, else false
//----------------------------------------------------------
bool LinkProgram(GLuint p_uiProg)
{
    GLint iStatus;
    
    glLinkProgram(p_uiProg);
    
#if defined(DEBUG)
    GLint iLogLength;
    glGetProgramiv(p_uiProg, GL_INFO_LOG_LENGTH, &iLogLength);
    if (iLogLength > 0)
    {
        GLchar* pLog = (GLchar *)malloc(iLogLength);
        glGetProgramInfoLog(p_uiProg, iLogLength, &iLogLength, pLog);
        printf("Program link log:\n%s\n", pLog);
        free(pLog);
    }
#endif
    
    glGetProgramiv(p_uiProg, GL_LINK_STATUS, &iStatus);
    if (iStatus == 0)
        return false;
    
    return true;
}
//----------------------------------------------------------
// Loads a vertex and pixel shader from the given files, and
// compiles and links them into a program. Will return 0 on
// failure (and print errors to stdout), else the created
// program object
//----------------------------------------------------------
GLuint LoadShaders(const std::string& p_strVSFile, const std::string& p_strPSFile)
{
    GLuint uiVS, uiPS;
    
    // 1. Create and compile vertex shader.
    if( !CompileShader(&uiVS, GL_VERTEX_SHADER, p_strVSFile))
	{
        printf("Failed to compile vertex shader\n");
        return 0;
    }
    
    // 2. Create and compile fragment shader.
    if( !CompileShader(&uiPS, GL_FRAGMENT_SHADER, p_strPSFile))
	{
        printf("Failed to compile pixel shader\n");
		glDeleteShader(uiVS);
        return 0;
    }

    // 3. Create shader program that we'll (hopefully) eventually return
    GLuint uiProgram = glCreateProgram();
    
    // 4. Attach vertex shader and pixel shader to program.
    glAttachShader(uiProgram, uiVS);
    glAttachShader(uiProgram, uiPS);
    
    // 5. Link program.
    if( !LinkProgram(uiProgram) )
    {
        printf("Failed to link program: %d\n", uiProgram);
        
        if( uiVS )
        {
            glDeleteShader(uiVS);
        }
        if( uiPS )
        {
            glDeleteShader(uiPS);
        }
        if( uiProgram )
        {
            glDeleteProgram(uiProgram);
        }
        
        return 0;
    }
    
    // Release vertex and fragment shaders.
    if( uiVS )
        glDeleteShader(uiVS);
    if( uiPS )
        glDeleteShader(uiPS);
    
    return uiProgram;
}

}
