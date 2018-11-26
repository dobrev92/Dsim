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
		return DS_FAIL;	
	}

	if (CreateWindow(fullscreen, samples, width, height) == DS_FAIL) {
		glfwTerminate();
		return DS_FAIL;
	}
	
	glfwMakeContextCurrent(m_Window);

	// Initialize GLEW
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		dbg_info("glewInit() != GLEW_OK\n");
		return DS_FAIL;
	}	

	glfwSetTime(0);
	glfwGetCursorPos(m_Window, &xRef, &yRef);

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
	//glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	if (fullscreen) {
		m_Window = glfwCreateWindow( width, height, "Simulation Window", glfwGetPrimaryMonitor(), NULL);
	} else {
		m_Window = glfwCreateWindow( width, height, "Simulation Window", NULL, NULL);
	}

	glfwSetInputMode(m_Window, GLFW_STICKY_KEYS, GL_TRUE);
	glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	glfwSetCursorPosCallback(m_Window, GraphicsWindowGLFW::GLFWCursorPositionCallback);
	glfwSetMouseButtonCallback(m_Window, GraphicsWindowGLFW::GLFWMouseButtonCallback);
	glfwSetWindowSizeCallback(m_Window, GLFWWindowSizeCallback);

	if (!m_Window) {
		rc = DS_FAIL;
	}

	return rc;
}

void GraphicsWindowGLFW::SetMouseMoveCallback(MouseMoveCallback a_cb)
{
	dbg_info("\n");
	m_MousePosCallback = a_cb;
}

void GraphicsWindowGLFW::SetMouseButtonCallback(MouseButtonCallback a_cb)
{
	dbg_info("\n");
	m_MouseButtonCallback = a_cb;
}

void GraphicsWindowGLFW::SetWindowSizeCallback(WindowSizeCallback a_cb)
{
	dbg_info("\n");
	m_WindowSizeCallback = a_cb;
}

void GraphicsWindowGLFW::DisableCursor(bool disable)
{
	if(disable)
		glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	else
		glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void GraphicsWindowGLFW::GetRelativeMouseMovement(double *relX, double *relY)
{
	double posX, posY;

	glfwGetCursorPos(m_Window, &posX, &posY);
	if (relX)
		*relX = xRef - posX;

	if (relY)
		*relY = yRef - posY;

	xRef = posX;
	yRef = posY;
}

DS_KEY_STATE GraphicsWindowGLFW::GetKey(DS_KEY key)
{
	int state;

	state = glfwGetKey(m_Window, key);
	return (DS_KEY_STATE)state;
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

void GraphicsWindowGLFW::GLFWCursorPositionCallback(GLFWwindow* window, double xpos, double ypos)
{
	if(m_MousePosCallback && mCalee)
		(*m_MousePosCallback)(mCalee, xpos, ypos);
}

void GraphicsWindowGLFW::GLFWMouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	if(m_MouseButtonCallback && mCalee)
		(*m_MouseButtonCallback)(mCalee, button, action, mods);
}

void GraphicsWindowGLFW::GLFWWindowSizeCallback(GLFWwindow* window, int width, int height)
{
	if(m_WindowSizeCallback && mCalee)
		(*m_WindowSizeCallback)(mCalee, width, height);
}

void (*GraphicsWindowGLFW::m_MousePosCallback)(void *, double, double) = NULL;
void (*GraphicsWindowGLFW::m_MouseButtonCallback)(void *, int, int, int) = NULL;
void (*GraphicsWindowGLFW::m_WindowSizeCallback)(void *, int, int) = NULL;
void * GraphicsWindowGLFW::mCalee = NULL;
double GraphicsWindowGLFW::xRef = 0;
double GraphicsWindowGLFW::yRef = 0;

