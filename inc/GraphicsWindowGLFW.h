#ifndef __GRAPHICS_WINDOWGLFW_H__
#define __GRAPHICS_WINDOWGLFW_H__

#include "GraphicsWindow.h"
//#include <glfw3.h>

struct GLFWwindow;

namespace Dsim {

class GraphicsWindowGLFW : public GraphicsWindow {
	protected:
		GLFWwindow *m_Window;
		static MouseMoveCallback m_MouseMoveCallback;
		static MouseButtonCallback m_MouseButtonCallback;
		static WindowSizeCallback m_WindowSizeCallback;
	public:
		GraphicsWindowGLFW();
		ds_err Init(bool fullscreen, unsigned int samples, int width, int height);
		ds_err CreateWindow(int fullscreen, int samples, int width, int height);

		void SetMouseMoveCallback(MouseMoveCallback a_cb);
		void SetMouseButtonFunc(MouseButtonCallback a_cb);
		void SetWindowSizeFunc(WindowSizeCallback a_cb);

		bool IsActive();

		ds_err SwapBuffers();
		ds_err ContextSwitch();
		virtual ~GraphicsWindowGLFW() {}
};
}
#endif //__GRAPHICS_WINDOWGLFW_H__
