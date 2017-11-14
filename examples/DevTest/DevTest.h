#ifndef __DEV_TEST_H__
#define __DEV_TEST_H__

#include "TestCommon.h"
#include "Render/GL/GLBufferObject.h"
#include "Render/GL/GLShaderObject.h"

class DevTest : public TestCommon {
	protected:
		Dsim::ShaderObject *vshader;
		Dsim::ShaderObject *pshader;
		Dsim::GLVertexBuffer *vbuf;
		Dsim::ds_err InitResources();
	public:
		DevTest();
		~DevTest();	
};

#endif //__DEV_TEST_H__
