#include "DevTest.h"
#include "math/linear_algebra.h"
#include "debug.h"
#include "Node.h"

char vertex_transform[] = 
"#version 330 core\n"

"// Input vertex data, different for all executions of this shader.\n"
"layout(location = 0) in vec4 vertexPosition_modelspace;\n"

"// Values that stay constant for the whole mesh.\n"
"uniform mat4 World;\n"
"//uniform mat4 ViewProj;\n"

"void main()\n"
"{\n"
"	gl_Position = World * vertexPosition_modelspace;\n"
"}\n";


char pixel_transform[] =
"#version 330 core\n"

"// Ouput data\n"
"out vec3 color;\n"

"void main()\n"
"{\n"
"	// Output color = green\n"
"	color = vec3(0,0,1);\n"
"}\n";

using namespace Dsim;
using namespace std;

int main()
{
	DevTest app;
	app.Run();
	return 0;
}

DevTest::DevTest()
{
	dbg_info("\n");
	vshader = NULL;
	pshader = NULL;
	program = NULL;
	vbuf = NULL;
	Matrix4x4PerspectiveFov(&Proj, PI / 4, 4.0f / 3.0f, 1, 30);
	InitResources();
}

DevTest::~DevTest()
{
	dbg_info("\n");
	if (vbuf) {
		delete vbuf;
	}

	if (program) {
		delete program;
	}

	if (vshader) {
		delete vshader;
	}

	if (pshader) {
		delete pshader;
	}

	if (MVP) {
		delete MVP;
	}
}

ds_err DevTest::InitResources()
{
	dbg_info("\n");

	window->SetMouseMoveCallback(DevTest::mSMouseMoveCallback);
	window->SetMouseButtonCallback(DevTest::mSMouseButtonCallback);
	window->SetWindowSizeCallback(DevTest::mSWindowResizeCallback);
	window->SetCalleeObj(this);
		
	vshader = new GLShaderObject(SHADER_VERTEX);
	vshader->setShaderSource(vertex_transform);
	vshader->CompileShader();

	pshader = new GLShaderObject(SHADER_FRAGMENT);
	pshader->setShaderSource(pixel_transform);
	pshader->CompileShader();

	program = new GLGpuProgram;
	program->AttachVertexShader(vshader);
	program->AttachFragmentShader(pshader);
	program->LinkProgram();

	MVP = new GLUniform;

	program->GetUniformLocation(MVP, "World");
	

	vbuf = new GLBufferObject;
	vbuf->SetTarget(VERTEX_BUFFER);

	Vector4 vec[3];
	vec[0] = Vector4(-1.0f, -1.0f, 0.0f, 1.0f);
	vec[1] = Vector4(1.0f, -1.0f, 0.0f, 1.0f);
	vec[2] = Vector4(0.0f, 1.0f, 0.0f, 1.0f);

	vbuf->BindBuffer();
	vbuf->BufferData(3 * sizeof(Vector4), vec);

	Node *node;
	Node *child;

	node = new Node;
	child = new Node;

	node->AddChild(child);
	delete node;

	return DS_SUCCESS;

}

void DevTest::MainLoop()
{
	Matrix4x4 View, ViewProj;
	static scalar angle = 0;
	angle += 0.1f;
	Matrix4x4 rot;
	Matrix4x4RotationY(&rot, angle);
	Vector3 pos(0.0f, 0.0f, 3.0f);
	Vector3 lookAt(0.0f, 0.0f, 0.0f);
	Vector3 up(0.0f, 1.0f, 0.0f);
	Matrix4x4ViewLookAt(&View, &pos, &lookAt, &up);
	ViewProj = Proj * View * rot;

	render->ClearScreen();
	program->UseProgram();
	MVP->Set(&ViewProj);
	vbuf->BindBuffer();
	render->VertexAttribPointer(0, 4, DS_FLOAT, false, 0, NULL);
	render->DrawArrays(0, 3);
}


//MEMBER CALLBACKS
void DevTest::mMouseMoveCallback(double xpos, double ypos)
{
	//dbg_info("\n");
}

void DevTest::mMouseButtonCallback(int button, int action, int mods)
{
	//dbg_info("\n");
}

void DevTest::mWindowResizeCallback(int width, int height)
{
	//dbg_info("\n");
	Matrix4x4PerspectiveFov(&Proj, PI / 4, (scalar)width / (scalar)height, 1, 30);
	render->Viewport(0, 0, width, height);
}


//STATIC CALLBACKS
void DevTest::mSMouseMoveCallback(void *p_obj, double xpos, double ypos)
{
	DevTest *obj = (DevTest *)p_obj;
	obj->mMouseMoveCallback(xpos, ypos);
}

void DevTest::mSMouseButtonCallback(void *p_obj, int button, int action, int mods)
{
	DevTest *obj = (DevTest *)p_obj;
	obj->mMouseButtonCallback(button, action, mods);
}

void DevTest::mSWindowResizeCallback(void *p_obj, int width, int height)
{
	DevTest *obj = (DevTest *)p_obj;
	obj->mWindowResizeCallback(width, height);
}

