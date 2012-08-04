//-----------------------------------------------------------------------------
// File:			W_Common.h
// Original Author:	Gordon Wood
//
// Common functions used in all samples
//-----------------------------------------------------------------------------
#ifndef COMMON_H
#define COMMON_H

#include "W_Types.h"
#include <string>

namespace wolf
{
// Loads in a whole file and returns the contents. User is responsible for then
// delete[]-ing the data. Returns 0 if file not able to be loaded.
void* LoadWholeFile(const std::string& p_strFile);

// Loads in a vertex and pixel shader and combines them into a program
GLuint LoadShaders(const std::string& p_strVSFile, const std::string& p_strPSFile);
}

#endif
