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
}

ds_err TestCommon::InitWindow()
{
	dbg_info("\n");
	window = new GraphicsWindowGLFW;
	window->Init(false, 4, 848, 480);
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
}

ds_err TestCommon::Run()
{
	while (window->IsActive()) {
		MainLoop();
		render->RenderFrame();
	}

	return DS_SUCCESS;
}

