#ifndef __TEST_COMMON_H__
#define __TEST_COMMON_H__

#include "Render/GL/GLRender.h"
#include "GraphicsWindow.h"
#include "Node.h"

class TestCommon {
	protected:
		Dsim::GraphicsWindow *window;
		Dsim::GLRender *render;

		virtual Dsim::ds_err InitResources()=0;
		virtual void UpdateCamera();
		Dsim::ds_err InitWindow();
		Dsim::ds_err InitRender();
		Dsim::Node *Root;
		Dsim::Node *Camera;
		bool mRotateEnable;

		void mMouseMoveCallback(double xpos, double ypos);
		void mMouseButtonCallback(int button, int action, int mods);
		void mWindowResizeCallback(int width, int height);

		static void mSMouseMoveCallback(void *p_obj, double xpos, double ypos);
		static void mSMouseButtonCallback(void *p_obj, int button, int action, int mods);
		static void mSWindowResizeCallback(void *p_obj, int width, int height);
	public:
		TestCommon();
		virtual void MainLoop()=0;
		virtual Dsim::ds_err Run();
		virtual ~TestCommon();
};

#endif //__TEST_COMMON_H__
