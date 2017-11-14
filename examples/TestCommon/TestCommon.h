#ifndef __TEST_COMMON_H__
#define __TEST_COMMON_H__

#include "Render/GL/GLRender.h"

class TestCommon {
	protected:
		Dsim::GraphicsWindow *window;
		Dsim::Render *render;

		virtual Dsim::ds_err InitResources()=0;
		Dsim::ds_err InitWindow();
		Dsim::ds_err InitRender();
	public:
		TestCommon();
		virtual Dsim::ds_err Run();
		virtual ~TestCommon();
};

#endif //__TEST_COMMON_H__
