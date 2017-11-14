#include "Render/GL/GLBufferObject.h"
#include "debug.h"

using namespace Dsim;

GLVertexBuffer::GLVertexBuffer()
{
	dbg_info("\n");
	glGenBuffers(1, &mBufferID);
}

ds_err GLVertexBuffer::setBufferData(unsigned int size, void *data)
{
	return DS_SUCCESS;
}

ds_err GLVertexBuffer::bindBuffer()
{
	return DS_SUCCESS;
}

GLVertexBuffer::~GLVertexBuffer()
{
	dbg_info("\n");
	glDeleteBuffers(1, &mBufferID);
}

GLIndexBuffer::GLIndexBuffer()
{
	dbg_info("\n");
	glGenBuffers(1, &mBufferID);
}

ds_err GLIndexBuffer::setBufferData(unsigned int size, void *data)
{
	return DS_SUCCESS;
}

ds_err GLIndexBuffer::bindBuffer()
{
	return DS_SUCCESS;
}

GLIndexBuffer::~GLIndexBuffer()
{
	dbg_info("\n");
	glDeleteBuffers(1, &mBufferID);
}

