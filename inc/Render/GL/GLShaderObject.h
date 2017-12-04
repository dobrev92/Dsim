#ifndef __GL_SHADER_OBJECT_H__
#define __GL_SHADER_OBJECT_H__

#include <GL/glew.h>

#include "../ShaderObject.h"

namespace Dsim {

class GLShaderObject : public ShaderObject {
	protected:
		GLuint mGLShaderHandle;
	public:
		GLShaderObject(ShaderType type);

		GLuint GetGLHandle() { return mGLShaderHandle; }
		ds_err CompileShader();
		ds_err PreContextSwitch() {}
		ds_err PostContextSwitch() {}

		~GLShaderObject();
};

}

#endif //__GL_SHADER_OBJECT_H__

