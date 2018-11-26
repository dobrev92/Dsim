#ifndef __GRAPHICS_WINDOW_H__
#define __GRAPHICS_WINDOW_H__

#include "ds_err.h"

namespace Dsim {

typedef enum {
	DS_KEY_W		= 87,
	DS_KEY_S		= 83,
	DS_KEY_A		= 65,
	DS_KEY_D		= 68
} DS_KEY;

typedef enum {
	DS_MOUSE_BUTTON_1 	= 0,
	DS_MOUSE_BUTTON_2 	= 1,
	DS_MOUSE_BUTTON_3 	= 2,
	DS_MOUSE_BUTTON_4 	= 3,
	DS_MOUSE_BUTTON_5 	= 4,
	DS_MOUSE_BUTTON_6 	= 5,
	DS_MOUSE_BUTTON_LEFT	= DS_MOUSE_BUTTON_1,
	DS_MOUSE_BUTTON_RIGHT	= DS_MOUSE_BUTTON_2,
	DS_MOUSE_BUTTON_MIDDLE	= DS_MOUSE_BUTTON_3,
} DS_MOUSE_BUTTON;

typedef enum {
	DS_KEY_RELEASE	= 0,
	DS_KEY_PRESS	= 1,
	DS_KEY_REPEAT	= 2
} DS_KEY_STATE;

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

		virtual void DisableCursor(bool disable)=0;
		virtual void GetRelativeMouseMovement(double *relX, double *relY)=0;
		virtual DS_KEY_STATE GetKey(DS_KEY key)=0;

		virtual bool IsFullscreen() { return m_Fullscreen; }
		virtual bool IsActive()=0;
		virtual ds_err SwapBuffers()=0;
		virtual ds_err ContextSwitch()=0;

		virtual ~GraphicsWindow() {}
		
};
}
#endif //__GRAPHICS_WINDOW_H__
