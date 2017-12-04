#include "Render/GL/GLGpuProgram.h"
#include "debug.h"
#include "Render/GL/GLUniform.h"

using namespace Dsim;

GLGpuProgram::GLGpuProgram()
{
	dbg_info("\n");
	mGLProgramHandle = glCreateProgram();
}

ds_err GLGpuProgram::AttachVertexShader(GLShaderObject *VShader)
{
	if (!VShader) {
		dbg_info("VShader = NULL\n");
		return DS_FAIL;
	}

	if (VShader->getType() != SHADER_VERTEX) {
		dbg_info("VShader->getType() != SHADER_VERTEX\n");
		return DS_FAIL;
	}

	dbg_info("\n");
	mVertexShader = VShader;
	glAttachShader(mGLProgramHandle, mVertexShader->GetGLHandle());

	return DS_SUCCESS;
}

ds_err GLGpuProgram::AttachFragmentShader(GLShaderObject *FShader)
{
	if (!FShader) {
		dbg_info("FShader = NULL\n");
		return DS_FAIL;
	}

	if (FShader->getType() != SHADER_FRAGMENT) {
		dbg_info("FShader->getType() != SHADER_FRAGMENT\n");
		return DS_FAIL;
	}

	dbg_info("\n");
	mFragmentShader = FShader;
	glAttachShader(mGLProgramHandle, mFragmentShader->GetGLHandle());

	return DS_SUCCESS;
}

ds_err GLGpuProgram::LinkProgram()
{
	if (!mVertexShader) {
		dbg_info("mVertexShader == NULL\n");
		return DS_FAIL;
	}

	if (!mFragmentShader) {
		dbg_info("mFragmentShader == NULL\n");
		return DS_FAIL;
	}

	GLint infoLogLength = 0;
	GLint rc = -1;
	
	dbg_info("\n");
	glLinkProgram(mGLProgramHandle);

	//Handle errors
	glGetShaderiv(mGLProgramHandle, GL_LINK_STATUS, &rc);
	glGetShaderiv(mGLProgramHandle, GL_INFO_LOG_LENGTH, &infoLogLength);
	if (infoLogLength > 0) {
		char programErrorLog[infoLogLength + 1];
		glGetShaderInfoLog(mGLProgramHandle, infoLogLength, NULL, &programErrorLog[0]);
		dbg_info("Error Log\n%s\n", &programErrorLog);
		return DS_FAIL;
	}

	glDetachShader(mGLProgramHandle, mVertexShader->GetGLHandle());
	glDetachShader(mGLProgramHandle, mFragmentShader->GetGLHandle());

	return DS_SUCCESS;
}

void GLGpuProgram::UseProgram()
{
	glUseProgram(mGLProgramHandle);
}

void GLGpuProgram::GetUniformLocation(GLUniform *uniform, const char* name)
{
	dbg_info("\n");
	uniform->mUniformHandle = glGetUniformLocation(mGLProgramHandle, name);
}

GLGpuProgram::~GLGpuProgram()
{
	dbg_info("\n");
	glDeleteProgram(mGLProgramHandle);	
}
