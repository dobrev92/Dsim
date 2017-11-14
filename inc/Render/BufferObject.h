#ifndef __BUFFER_OBJECT_H__
#define __BUFFER_OBJECT_H__

#include "RenderResource.h"

namespace Dsim {

class BufferObject : public RenderResource
{
	protected:
		unsigned int mSize;
	public:
		virtual ds_err setBufferData(unsigned int size, void *data)=0;
		//virtual ds_err setBufferSubData()=0;
		//virtual ds_err getBufferData()=0;
		//virtual ds_err getBufferSubData()=0;
		virtual ds_err bindBuffer()=0;

		unsigned int GetSize() { return mSize; }
		virtual ~BufferObject() {}
};

class VertexBuffer : public BufferObject
{
	protected:
		unsigned int mNumVertices;
	public:
		unsigned int getNumVertices() { return mNumVertices; }
		virtual ~VertexBuffer() {}
};

class IndexBuffer : public BufferObject
{
	protected:
		unsigned mNumIndices;
	public:
		unsigned int getNumIndices() { return mNumIndices; }
		virtual ~IndexBuffer() {}
};

}
#endif //__BUFFER_OBJECT_H__
