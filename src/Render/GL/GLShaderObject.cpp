#include "Render/GL/GLShaderObject.h"
#include "debug.h"
#include <vector>

using namespace Dsim;

GLShaderObject::GLShaderObject(ShaderType type)
: ShaderObject(type)
{
	dbg_info("\n");
	mGLShaderHandle = 0;
	switch (type) {
		case SHADER_VERTEX:
			glCreateShader(GL_VERTEX_SHADER);
			break;
		case SHADER_FRAGMENT:
			glCreateShader(GL_FRAGMENT_SHADER);
			break;
		default:
			dbg_info("Invalid Shader Type\n");
			mType = SHADER_UNDEFINED;
			break;
	}
}

ds_err GLShaderObject::CompileShader()
{
	//Compile shader from source here
	GLint infoLogLength = 0;
	GLint rc = GL_FALSE;
	char const *sourcePointer = mShaderSrc.c_str();
	
	dbg_info("Compiling shader:\n%s\n", sourcePointer);
	glShaderSource(mGLShaderHandle, 1, &sourcePointer , NULL);
	glCompileShader(mGLShaderHandle);

	//Handle errors
	glGetShaderiv(mGLShaderHandle, GL_COMPILE_STATUS, &rc);
	glGetShaderiv(mGLShaderHandle, GL_INFO_LOG_LENGTH, &infoLogLength);
	dbg_info("GL_COMPILE_STATUS = %X\n", rc);
	dbg_info("infoLogLength = %d\n", infoLogLength);
	if (infoLogLength > 0) {
		dbg_info("Branch start\n");
		char shaderErrorLog[infoLogLength + 1];
		glGetShaderInfoLog(mGLShaderHandle, infoLogLength, NULL, &shaderErrorLog[0]);
		dbg_info("Error Log:\n");
		dbg_info("%s\n", &shaderErrorLog);
		dbg_info("Branch end\n");
		return DS_FAIL;
	}

	return DS_SUCCESS;
}

GLShaderObject::~GLShaderObject()
{
	dbg_info("\n");
	if (mGLShaderHandle) {
		glDeleteShader(mGLShaderHandle);
	}
}
