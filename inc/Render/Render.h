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

typedef enum {
	DS_BYTE,
	DS_UNSIGNED_BYTE,
	DS_SHORT,
	DS_UNSIGNED_SHORT,
	DS_INT,
	DS_UNSIGNED_INT,
	DS_HALF_FLOAT,
	DS_FLOAT,
	DS_DOUBLE
} DS_TYPE;

typedef enum {
	DS_POINTS,
	DS_LINE_STRIP,
	DS_LINE_LOOP,
	DS_LINES,
	DS_TRIANGLE_STRIP,
	DS_TRIANGLE_FAN,
	DS_TRIANGLES
} DS_PRIMITIVE_MODE;

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
		virtual ds_err Viewport(int x, int y, int width, int height)=0;
		virtual ds_err ClearScreen()=0;
		virtual ds_err DrawArrays(unsigned int first, unsigned int size)=0;
		virtual ds_err DrawIndexedLineLoop(int numIndices, const void* indices)=0;
		virtual ds_err DrawIndexedLines(int numIndices, const void* indices)=0;
		virtual ds_err DrawArraysInstanced(int first, int count, int primcount)=0;
		virtual ds_err VertexAttribPointer(unsigned int index, unsigned int size, DS_TYPE type, bool normalized,
			unsigned int stride, const void *pointer)=0;

		virtual ds_err RenderFrame()=0;
		virtual ds_err PreContextSwitch()=0;
		virtual ds_err PostContextSwitch()=0;

		RenderCaps* GetCaps() { return m_Caps; }
		virtual ~Render() {}
};

}

#endif //__Render_H__
