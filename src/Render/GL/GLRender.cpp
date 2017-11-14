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

	glClearColor(0.0f, 0.3f, 0.0f, 0.0f);

	return DS_SUCCESS;
}

ds_err GLRender::FillCaps()
{
	return DS_SUCCESS;
}

ds_err GLRender::ViewPort(int x, int y, int width, int height)
{
	return DS_SUCCESS;
}

ds_err GLRender::ClearScreen()
{
	glClear( GL_COLOR_BUFFER_BIT );
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

ds_err GLRender::RenderFrame()
{
	ClearScreen();
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

