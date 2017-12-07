#include "Render/GL/GLRender.h"
#include "debug.h"

using namespace Dsim;

GLRender::GLRender()
{
}

GLRender::GLRender(GraphicsWindow* a_GWindow)
{
	dbg_info("\n");
	m_GWindow = a_GWindow;
	Init();
}

ds_err GLRender::Init()
{
	dbg_info("\n");
	glGenVertexArrays(1, &mVertexArrayID);
	glBindVertexArray(mVertexArrayID);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	return DS_SUCCESS;
}

ds_err GLRender::FillCaps()
{
	return DS_SUCCESS;
}

ds_err GLRender::Viewport(int x, int y, int width, int height)
{
	glViewport(x, y, width, height);
	return DS_SUCCESS;
}

ds_err GLRender::ClearScreen()
{
	glClear( GL_COLOR_BUFFER_BIT );
	return DS_SUCCESS;
}

ds_err GLRender::DrawArrays(unsigned int first, unsigned int size)
{
	glDrawArrays(GL_TRIANGLES, first, size);
	return DS_SUCCESS;
}

ds_err GLRender::DrawIndexedLineLoop(int numIndices, const void* indices)
{
	return DS_SUCCESS;
}

ds_err GLRender::DrawIndexedLines(int numIndices, const void* indices)
{
	return DS_SUCCESS;
}

ds_err GLRender::DrawArraysInstanced(int first, int count, int primcount)
{
	return DS_SUCCESS;
}

ds_err GLRender::VertexAttribPointer(unsigned int index, unsigned int size, DS_TYPE type, bool normalized,
			unsigned int stride, const void *pointer)
{
	GLenum gl_type;

	switch (type) {
		case DS_BYTE:
			gl_type = GL_BYTE;
			break;

		case DS_UNSIGNED_BYTE:
			gl_type = GL_UNSIGNED_BYTE;
			break;

		case DS_SHORT:
			gl_type = GL_SHORT;
			break;

		case DS_UNSIGNED_SHORT:
			gl_type = GL_UNSIGNED_SHORT;
			break;

		case DS_INT:
			gl_type = GL_INT;
			break;

		case DS_UNSIGNED_INT:
			gl_type = GL_UNSIGNED_INT;
			break;

		case DS_HALF_FLOAT:
			gl_type = GL_HALF_FLOAT;
			break;

		case DS_FLOAT:
			gl_type = GL_FLOAT;
			break;

		case DS_DOUBLE:
			gl_type = GL_DOUBLE;
			break;
	}

	glEnableVertexAttribArray(index);
	glVertexAttribPointer(index, size, gl_type, normalized, stride, pointer);

	return DS_SUCCESS;
}

ds_err GLRender::RenderFrame()
{
	//ClearScreen();
	m_GWindow->SwapBuffers();
	return DS_SUCCESS;
}

ds_err GLRender::PreContextSwitch()
{
	return DS_SUCCESS;
}

ds_err GLRender::PostContextSwitch()
{
	return DS_SUCCESS;
}

GLRender::~GLRender()
{
	dbg_info("\n");
	glDeleteVertexArrays(1, &mVertexArrayID);
}

