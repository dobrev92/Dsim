#include "../inc/GraphicsWindowGLFW.h"
#include "../inc/debug.h"
#include <GL/glew.h>
#include <glfw3.h>

using namespace Dsim;

GraphicsWindowGLFW::GraphicsWindowGLFW()
{
	dbg_info("\n");
	m_Window = NULL;
}

ds_err GraphicsWindowGLFW::Init(bool fullscreen, unsigned int samples, int width, int height)
{   
	m_Fullscreen = false;
	if( !glfwInit() ) {
		dbg_info("glfwInit = 0\n");
		return DS_SUCCESS;
	}

	if (CreateWindow(fullscreen, samples, width, height) == DS_FAIL) {
		glfwTerminate();
		return DS_FAIL;
	}
	
	glfwMakeContextCurrent(m_Window);

	// Initialize GLEW
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		return DS_SUCCESS;
	}	

	glfwSetTime(0);

	return DS_SUCCESS;
}

ds_err GraphicsWindowGLFW::CreateWindow(int fullscreen, int samples, int width, int height)
{
	ds_err rc = DS_SUCCESS;

	glfwWindowHint(GLFW_SAMPLES, samples);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	if (fullscreen) {
		m_Window = glfwCreateWindow( width, height, "Simulation Window", glfwGetPrimaryMonitor(), NULL);
	} else {
		m_Window = glfwCreateWindow( width, height, "Simulation Window", NULL, NULL);
	}

	glfwSetInputMode(m_Window, GLFW_STICKY_KEYS, GL_TRUE);
	/*
	glfwSetCursorPosCallback(window, __GlfwWrapper::cursor_position_callback);
	glfwSetMouseButtonCallback(window, __GlfwWrapper::mouse_button_callback);
	glfwSetWindowSizeCallback(window, window_size_callback);
	*/

	if (!m_Window) {
		rc = DS_FAIL;
	}
	
	return rc;
}

void GraphicsWindowGLFW::SetMouseMoveCallback(MouseMoveCallback a_cb)
{
	dbg_info("\n");
}

void GraphicsWindowGLFW::SetMouseButtonFunc(MouseButtonCallback a_cb)
{
	dbg_info("\n");
}

void GraphicsWindowGLFW::SetWindowSizeFunc(WindowSizeCallback a_cb)
{
	dbg_info("\n");
}

bool GraphicsWindowGLFW::IsActive()
{
	if (glfwGetKey(m_Window, GLFW_KEY_ESCAPE) == GLFW_PRESS || glfwWindowShouldClose(m_Window) == 1) {
		return false;
	}

	return true;
}

ds_err GraphicsWindowGLFW::SwapBuffers()
{
	glfwPollEvents();
	glfwSwapBuffers(m_Window);
	return DS_SUCCESS;
}

ds_err GraphicsWindowGLFW::ContextSwitch()
{
	dbg_info("\n");
	return DS_SUCCESS;
}

