#include "TestCommon.h"
#include "GraphicsWindowGLFW.h"
#include "debug.h"

using namespace std;
using namespace Dsim;

TestCommon::TestCommon()
{
	dbg_info("\n");
	window = NULL;
	render = NULL;

	InitWindow();
	InitRender();

	Root = new Node;
	Camera = new Node;
	Root->AddChild(Camera);

	Camera->Translate(0.0f, 0.0f, 5.0f);
}

ds_err TestCommon::InitWindow()
{
	dbg_info("\n");
	window = new GraphicsWindowGLFW;
	window->Init(true, 4, 1600, 900);

	//Init the callbacks
	window->SetMouseMoveCallback(TestCommon::mSMouseMoveCallback);
	window->SetMouseButtonCallback(TestCommon::mSMouseButtonCallback);
	window->SetWindowSizeCallback(TestCommon::mSWindowResizeCallback);
	window->SetCalleeObj(this);

	return DS_SUCCESS;
}

ds_err TestCommon::InitRender()
{
	dbg_info("\n");
	render = new GLRender(window);
	return DS_SUCCESS;
}

TestCommon::~TestCommon()
{
	dbg_info("\n");
	if (render) {
		delete render;
	}

	if (window) {
		delete window;
	}

	if (Root) {
		delete Root;
	}
}

void TestCommon::UpdateCamera()
{
	double xMov, yMov;

	window->GetRelativeMouseMovement(&xMov, &yMov);
	if (xMov) {
		Vector3 axis(0.0f, 1.0f, 0.0f);
		Camera->Rotate(axis, 0.001f * xMov);
	}

	if (yMov) {
		Vector3 axis(1.0f, 0.0f, 0.0f);
		Camera->Rotate(axis, 0.001f * yMov);
	}

	if(window->GetKey(DS_KEY_W) == DS_KEY_PRESS) {
		Camera->Translate(0.0f, 0.0f, - 0.1f, TS_LOCAL);
	}

	if(window->GetKey(DS_KEY_S) == DS_KEY_PRESS) {
		Camera->Translate(0.0f, 0.0f, 0.1f, TS_LOCAL);
	}

	if(window->GetKey(DS_KEY_A) == DS_KEY_PRESS) {
		Camera->Translate(- 0.1f, 0.0f, 0.0f, TS_LOCAL);
	}

	if(window->GetKey(DS_KEY_D) == DS_KEY_PRESS) {
		Camera->Translate(0.1f, 0.0f, 0.0f, TS_LOCAL);
	}
}

ds_err TestCommon::Run()
{
	while (window->IsActive()) {
		UpdateCamera();
		MainLoop();
		render->RenderFrame();
	}

	return DS_SUCCESS;
}

//MEMBER CALLBACKS
void TestCommon::mMouseMoveCallback(double xpos, double ypos)
{
	//dbg_info("\n"
}

void TestCommon::mMouseButtonCallback(int button, int action, int mods)
{
	//dbg_info("\n");
}

void TestCommon::mWindowResizeCallback(int width, int height)
{
	//dbg_info("\n");
	//Matrix4x4PerspectiveFov(&Proj, PI / 4, (scalar)width / (scalar)height, 1, 30);
	render->Viewport(0, 0, width, height);
}


//STATIC CALLBACKS
void TestCommon::mSMouseMoveCallback(void *p_obj, double xpos, double ypos)
{
	TestCommon *obj = (TestCommon *)p_obj;
	obj->mMouseMoveCallback(xpos, ypos);
}

void TestCommon::mSMouseButtonCallback(void *p_obj, int button, int action, int mods)
{
	TestCommon *obj = (TestCommon *)p_obj;
	obj->mMouseButtonCallback(button, action, mods);
}

void TestCommon::mSWindowResizeCallback(void *p_obj, int width, int height)
{
	TestCommon *obj = (TestCommon *)p_obj;
	obj->mWindowResizeCallback(width, height);
}
