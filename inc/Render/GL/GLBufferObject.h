#ifndef __GL_BUFFER_OBJECT_H__
#define __GL_BUFFER_OBJECT_H__

#include <GL/glew.h>

#include "../BufferObject.h"

namespace Dsim {

class GLVertexBuffer :  public VertexBuffer
{
	protected:
		GLuint mBufferID;
	public:
		GLVertexBuffer();
		ds_err setBufferData(unsigned int size, void *data);
		ds_err bindBuffer();
		ds_err PreContextSwitch() {}
		ds_err PostContextSwitch() {}
		~GLVertexBuffer();
};

class GLIndexBuffer: public IndexBuffer
{
	protected:
		GLuint mBufferID;
	public:
		GLIndexBuffer();
		ds_err setBufferData(unsigned int size, void *data);
		ds_err bindBuffer();
		ds_err PreContextSwitch() {}
		ds_err PostContextSwitch() {}
		~GLIndexBuffer();
};

}

#endif //__GL_BUFFER_OBJECT_H__
