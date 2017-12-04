#ifndef __GL_GPU_PROGRAM_H__
#define __GL_GPU_PROGRAM_H__

#include "Render/GL/GLShaderObject.h"

namespace Dsim {

class GLUniform;

class GLGpuProgram
{
	protected:
		GLuint mGLProgramHandle;
		GLShaderObject *mVertexShader;
		GLShaderObject *mFragmentShader;

	public:
		GLGpuProgram();

		ds_err AttachVertexShader(GLShaderObject *VShader);
		ds_err AttachFragmentShader(GLShaderObject *FShader);

		ds_err LinkProgram();
		void UseProgram();
		void GetUniformLocation(GLUniform *uniform, const char* name);

		virtual ~GLGpuProgram();
};

}

#endif //__GL_GPU_PROGRAM_H__
