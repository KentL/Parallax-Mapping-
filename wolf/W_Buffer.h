//-----------------------------------------------------------------------------
// File:			W_Buffer.h
// Original Author:	Gordon Wood
//
// Base class for a buffer that is used by the rendering API. Concrete
// subclasses will be for an IndexBuffer and a VertexBuffer
//-----------------------------------------------------------------------------
#ifndef W_BUFFER_H
#define W_BUFFER_H

namespace wolf
{
class Buffer
{
	public:
		//-------------------------------------------------------------------------
		// PUBLIC INTERFACE
		//-------------------------------------------------------------------------
		Buffer() {}
		virtual ~Buffer() {}
		
		virtual void Bind() = 0;
		virtual void Write(const void* p_pData, int p_iLength = -1 ) = 0;
		//-------------------------------------------------------------------------

	private:
		//-------------------------------------------------------------------------
		// PRIVATE MEMBERS
		//-------------------------------------------------------------------------
		
		//-------------------------------------------------------------------------
};

}

#endif
