//-----------------------------------------------------------------------------
// File:			W_IndexBuffer.h
// Original Author:	Gordon Wood
//
// Derived class from wolf::Buffer, this one describing specifically a index
// buffer
//-----------------------------------------------------------------------------
#ifndef W_INDEXBUFFER_H
#define W_INDEXBUFFER_H

#include "W_Types.h"
#include "W_Buffer.h"

namespace wolf
{
class IndexBuffer : public Buffer
{
	public:
		//-------------------------------------------------------------------------
		// PUBLIC INTERFACE
		//-------------------------------------------------------------------------
		IndexBuffer(unsigned int p_uiNumIndices);
		virtual ~IndexBuffer();
		
		virtual int GetNumIndices() const { return m_uiLength / 2; }
		virtual void Bind();
		virtual void Write(const void* p_pData, int p_iLength = -1);
		//-------------------------------------------------------------------------

	private:
		//-------------------------------------------------------------------------
		// PRIVATE MEMBERS
		//-------------------------------------------------------------------------
		unsigned int		m_uiLength;	
		GLuint				m_uiBuffer;
		//-------------------------------------------------------------------------
};

}

#endif

