#include "Render/GL/GLBufferObject.h"
#include "debug.h"

using namespace Dsim;

GLBufferObject::GLBufferObject()
{
	dbg_info("\n");
	glGenBuffers(1, &buff);
}

void GLBufferObject::SetTarget(BufferTarget target)
{
	switch(target) {
		case VERTEX_BUFFER:
			mTarget =  GL_ARRAY_BUFFER;
			break;

		case INDEX_BUFFER:
			mTarget = GL_ELEMENT_ARRAY_BUFFER;
			break;
	}
}

void GLBufferObject::BufferData(unsigned int size, const void *data)
{
	dbg_info("\n");
	BindBuffer();
	glBufferData(mTarget, size, data, GL_STATIC_DRAW);
}

void GLBufferObject::BindBuffer()
{
	glBindBuffer(mTarget, buff);
}

GLBufferObject::~GLBufferObject()
{
	dbg_info("\n");
	glDeleteBuffers(1, &buff);
}
