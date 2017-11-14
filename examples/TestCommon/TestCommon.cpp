#include "TestCommon.h"
#include "GraphicsWindowGLFW.h"

using namespace std;
using namespace Dsim;

TestCommon::TestCommon()
{
	window = NULL;
	render = NULL;

	InitWindow();
	InitRender();
}

ds_err TestCommon::InitWindow()
{
	window = new GraphicsWindowGLFW;
	window->Init(false, 1, 848, 480);
	return DS_SUCCESS;
}

ds_err TestCommon::InitRender()
{
	render = new GLRender(window);
	return DS_SUCCESS;
}

TestCommon::~TestCommon()
{
	if (render) {
		delete render;
	}

	if (window) {
		delete window;
	}
}

ds_err TestCommon::Run()
{
	while (window->IsActive()) {
		render->RenderFrame();
	}

	return DS_SUCCESS;
}

