#ifndef __GL_BUFFER_OBJECT_H__
#define __GL_BUFFER_OBJECT_H__

#include <GL/glew.h>

#include "../BufferObject.h"

namespace Dsim {

typedef enum {
	VERTEX_BUFFER,
	INDEX_BUFFER,
} BufferTarget;

class GLBufferObject
{
	protected:
		unsigned int size;
		GLenum mTarget;
		GLenum mUsage;
		GLuint buff;
	public:
		GLBufferObject();

		void SetTarget(BufferTarget target);
		void BufferData(unsigned int size, const void *data);
		void BindBuffer();

		virtual ~GLBufferObject();

};

}

#endif //__GL_BUFFER_OBJECT_H__
