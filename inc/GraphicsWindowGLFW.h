#ifndef __GRAPHICS_WINDOWGLFW_H__
#define __GRAPHICS_WINDOWGLFW_H__

#include "GraphicsWindow.h"

struct GLFWwindow;

namespace Dsim {

class GraphicsWindowGLFW : public GraphicsWindow {
	protected:
		GLFWwindow *m_Window;

		//custom callbacks
		static MouseMoveCallback m_MousePosCallback;
		static MouseButtonCallback m_MouseButtonCallback;
		static WindowSizeCallback m_WindowSizeCallback;

		//Object containing callbacks
		static void *mCalee;

		//GLFW specific callbacks
		static void GLFWCursorPositionCallback(GLFWwindow* window, double xpos, double ypos);
		static void GLFWMouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
		static void GLFWWindowSizeCallback(GLFWwindow* window, int width, int height);

		//Will be used to give relative mouse movement;
		static double xRef, yRef;
	public:
		GraphicsWindowGLFW();
		ds_err Init(bool fullscreen, unsigned int samples, int width, int height);
		ds_err CreateWindow(int fullscreen, int samples, int width, int height);

		void SetMouseMoveCallback(MouseMoveCallback a_cb);
		void SetMouseButtonCallback(MouseButtonCallback a_cb);
		void SetWindowSizeCallback(WindowSizeCallback a_cb);
		void SetCalleeObj(void *aCalee) { mCalee = aCalee; }

		void GetRelativeMouseMovement(double *relX, double *relY);
		DS_KEY_STATE GetKey(DS_KEY key);

		bool IsActive();

		ds_err SwapBuffers();
		ds_err ContextSwitch();
		virtual ~GraphicsWindowGLFW() {}
};
}
#endif //__GRAPHICS_WINDOWGLFW_H__
