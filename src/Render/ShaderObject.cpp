#include "Render/ShaderObject.h"
#include "debug.h"

using namespace Dsim;

ShaderObject::ShaderObject(ShaderType type)
{
	mType = type;
	mIsCompiled = false;
}

ds_err ShaderObject::setShaderSource(std::string source)
{
	mShaderSrc = source;
	return DS_SUCCESS;
}

ds_err ShaderObject::loadShaderSourceFromFile(std::string fileName)
{
	std::ifstream sourceFile;
	std::string src;

	sourceFile.open(fileName.c_str(), std::ios::binary);
	if(!sourceFile.is_open())
	{
		dbg_info("Error: can't open file %s\n", fileName.c_str());
        	return DS_INVALID_FILE;
	}

	dbg_info("Loading shader source file %s\n", fileName.c_str());
	mShaderFileName = fileName;
	std::string line = "";
	while(getline(sourceFile, line)) {
		src += line + "\n";
	}
	sourceFile.close();

	setShaderSource(src);
	return DS_SUCCESS;
}

