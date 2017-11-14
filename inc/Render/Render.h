#ifndef __RENDER_H__
#define __RENDER_H__

#include "../ds_err.h"
#include "../GraphicsWindow.h"

namespace Dsim {

struct RenderCaps
{
	int placeholder;
	int placeholder2;
};

class Render
{
	protected:
		GraphicsWindow *m_GWindow;
		RenderCaps *m_Caps;

		virtual ds_err Init()=0;
		virtual ds_err FillCaps()=0;

	public:
		Render() {}
		Render(GraphicsWindow *a_GWindow) {}
		virtual ds_err ViewPort(int x, int y, int width, int height)=0;
		virtual ds_err ClearScreen()=0;
		virtual ds_err DrawIndexedLineLoop(int numIndices, const void* indices)=0;
		virtual ds_err DrawIndexedLines(int numIndices, const void* indices)=0;
		virtual ds_err DrawArraysInstanced(int first, int count, int primcount)=0;
		virtual ds_err RenderFrame()=0;
		virtual ds_err PreContextSwitch()=0;
		virtual ds_err PostContextSwitch()=0;

		RenderCaps* GetCaps() { return m_Caps; }
		virtual ~Render() {}
};

}

#endif //__Render_H__
