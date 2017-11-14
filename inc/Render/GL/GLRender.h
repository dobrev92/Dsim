#ifndef __GLRender_H__
#define __GLRender_H__

#include "../Render.h"
#include <GL/glew.h>

namespace Dsim {

class GLRender : public Render
{
	protected:
		GLuint mVertexArrayID;
		ds_err Init();
		ds_err FillCaps();

	public:
		GLRender();
		GLRender(GraphicsWindow* a_GWindow);
		~GLRender();

		ds_err ViewPort(int x, int y, int width, int height);
		ds_err ClearScreen();
		ds_err DrawIndexedLineLoop(int numIndices, const void* indices);
		ds_err DrawIndexedLines(int numIndices, const void* indices);
		ds_err DrawArraysInstanced(int first, int count, int primcount);
		ds_err RenderFrame();
		ds_err PreContextSwitch();
		ds_err PostContextSwitch();
};

}

#endif // __GLRENDER_H__

