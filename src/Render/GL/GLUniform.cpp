#include "Render/GL/GLUniform.h"

using namespace Dsim;

void GLUniform::Set(Matrix4x4 *mat)
{
	glUniformMatrix4fv(mUniformHandle, 1, GL_FALSE, mat->GetPointer());
}

