#ifndef __GL_UNIFORM_H__
#define __GL_UNIFORM_H__

#include <GL/glew.h>

#include "math/linear_algebra.h"

namespace Dsim {

class GLUniform
{
	friend class GLGpuProgram;

	protected:
		GLuint mUniformHandle;
	public:
		void Set(Matrix4x4 *mat);
};

}

#endif //__GL_UNIFORN_H__
