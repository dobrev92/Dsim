#ifndef __GL_SHADER_OBJECT_H__
#define __GL_SHADER_OBJECT_H__

#include <GL/glew.h>

#include "../ShaderObject.h"

namespace Dsim {

char vertex_transform[] = 
"#version 330 core\n"

"// Input vertex data, different for all executions of this shader.\n"
"layout(location = 0) in vec3 vertexPosition_modelspace;\n"

"// Values that stay constant for the whole mesh.\n"
"uniform mat4 World;\n"
"uniform mat4 ViewProj;\n"

"void main()\n"
"{\n"
"	vec4 vertex = vec4(vertexPosition_modelspace,1);\n"
"	vec4 WorldVertex = World * vertex;\n"
"	gl_Position = ViewProj * WorldVertex;\n"
"	//Output position of the vertex, in clip space : MVP * position\n"
"}\n";


char pixel_transform[] =
"#version 330 core\n"

"// Ouput data\n"
"out vec3 color;\n"

"void main()\n"
"{\n"
"	// Output color = green\n"
"	color = vec3(0,1,0);\n"
"}\n";

class GLShaderObject : public ShaderObject {
	protected:
		GLuint mGLShaderHandle;
	public:
		GLShaderObject(ShaderType type);

		ds_err CompileShader();
		ds_err PreContextSwitch() {}
		ds_err PostContextSwitch() {}

		~GLShaderObject();
};

}

#endif //__GL_SHADER_OBJECT_H__

