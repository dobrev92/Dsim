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

	Matrix3x3 mat(3);
	Vector3 vec1 = mat.GetRow(0);
	Vector3 vec2 = mat.GetRow(1); 
	Vector3 vec3 = mat.GetRow(2);

	dbg_info("vec1 = [%2f, %2f, %2f]\n", vec1.X(), vec1.Y(), vec1.Z());
	dbg_info("vec2 = [%2f, %2f, %2f]\n", vec2.X(), vec2.Y(), vec2.Z());
	dbg_info("vec3 = [%2f, %2f, %2f]\n", vec3.X(), vec3.Y(), vec3.Z());

	return DS_SUCCESS;
}

