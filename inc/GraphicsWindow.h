#ifndef __GRAPHICS_WINDOW_H__
#define __GRAPHICS_WINDOW_H__

#include "ds_err.h"

namespace Dsim {

typedef void (*MouseMoveCallback)(void *, double, double);
typedef void (*MouseButtonCallback)(void *, int, int, int);
typedef void (*WindowSizeCallback)(void *, int, int);

class GraphicsWindow {
	protected:
		bool m_Fullscreen;
	public:
		GraphicsWindow() {}
		virtual ds_err Init(bool fullscreen, unsigned int samples, int width, int height)=0;
		virtual ds_err CreateWindow(int fullscreen, int samples, int width, int height)=0;
		virtual void SetMouseMoveCallback(MouseMoveCallback a_cb)=0;
		virtual void SetMouseButtonCallback(MouseButtonCallback a_cb)=0;
		virtual void SetWindowSizeCallback(WindowSizeCallback a_cb)=0;
		virtual void SetCalleeObj(void *aCallee)=0;

		virtual bool IsFullscreen() { return m_Fullscreen; }
		virtual bool IsActive()=0;
		virtual ds_err SwapBuffers()=0;
		virtual ds_err ContextSwitch()=0;

		virtual ~GraphicsWindow() {}
		
};
}
#endif //__GRAPHICS_WINDOW_H__
