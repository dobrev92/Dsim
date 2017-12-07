#ifndef __TEST_COMMON_H__
#define __TEST_COMMON_H__

#include "Render/GL/GLRender.h"
#include "GraphicsWindowGLFW.h"

class TestCommon {
	protected:
		Dsim::GraphicsWindow *window;
		Dsim::GLRender *render;

		virtual Dsim::ds_err InitResources()=0;
		Dsim::ds_err InitWindow();
		Dsim::ds_err InitRender();
	public:
		TestCommon();
		virtual void MainLoop()=0;
		virtual Dsim::ds_err Run();
		virtual ~TestCommon();
};

#endif //__TEST_COMMON_H__
