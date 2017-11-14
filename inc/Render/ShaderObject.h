#ifndef __SHADER_OBJECT_H__
#define __SHADER_OBJECT_H__

#include <string>
#include <fstream>

#include "RenderResource.h"
#include "../ds_err.h"

namespace Dsim {

typedef enum {
	SHADER_VERTEX,
	SHADER_FRAGMENT,
	SHADER_UNDEFINED = -1,
}ShaderType;

class ShaderObject : public RenderResource {
	protected:
		ShaderType mType;
		std::string mShaderFileName;
		std::string mShaderSrc;
		bool mIsCompiled;
	public:
		ShaderObject(ShaderType type);

		bool isCompiled() { return mIsCompiled; }
		ShaderType getType() { return mType; }
		std::string getSource() { return mShaderSrc; }
		std::string getShaderFileName() { return mShaderFileName; }

		ds_err setShaderSource(std::string source);
		ds_err loadShaderSourceFromFile(std::string fileName);
		virtual ds_err CompileShader() = 0;

		virtual ~ShaderObject() {}
		
};

}

#endif //__SHADER_OBJECT_H__

