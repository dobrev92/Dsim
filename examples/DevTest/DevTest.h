#ifndef __DEV_TEST_H__
#define __DEV_TEST_H__

#include "TestCommon.h"
#include "Render/GL/GLBufferObject.h"
#include "Render/GL/GLShaderObject.h"
#include "Render/GL/GLGpuProgram.h"
#include "Render/GL/GLUniform.h"
#include "math/linear_algebra.h"

class DevTest : public TestCommon {
	protected:
		Dsim::GLShaderObject *vshader;
		Dsim::GLShaderObject *pshader;
		Dsim::GLGpuProgram *program;
		Dsim::GLUniform *MVP;
		Dsim::GLBufferObject *vbuf;
		Dsim::Matrix4x4 Proj;
		Dsim::ds_err InitResources();

		void mMouseMoveCallback(double xpos, double ypos);
		void mMouseButtonCallback(int button, int action, int mods);
		void mWindowResizeCallback(int width, int height);

		static void mSMouseMoveCallback(void *p_obj, double xpos, double ypos);
		static void mSMouseButtonCallback(void *p_obj, int button, int action, int mods);
		static void mSWindowResizeCallback(void *p_obj, int width, int height);

	public:
		void MainLoop();
		GLuint LoadShaders();
		DevTest();
		~DevTest();	
};

#endif //__DEV_TEST_H__
