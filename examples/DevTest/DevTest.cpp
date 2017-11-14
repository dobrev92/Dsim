#include "DevTest.h"
#include "math/linear_algebra.h"
#include "Render/GL/GLRender.h"
#include "debug.h"

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
	vshader = NULL;
	pshader = NULL;
	vbuf = NULL;
	InitResources();
}

DevTest::~DevTest()
{
	if (vbuf) {
		delete vbuf;
	}

	if (vshader) {
		delete vshader;
	}

	if (pshader) {
		delete pshader;
	}
}

ds_err DevTest::InitResources()
{
	ds_err rc;

	Vector2 vec1(3, 5);
	Vector2 vec2(1, 2);
	Vector2 res = 3.0f * vec1;

	dbg_info("vec1 = [%2f, %2f]\n", vec1.X(), vec1.Y());
	dbg_info("vec2 = [%2f, %2f]\n", vec2.X(), vec2.Y());
	dbg_info("res = [%2f, %2f]\n", res.X(), res.Y());

	return DS_SUCCESS;
}

