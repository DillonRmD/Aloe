#include "Shader.h"
#include <GL\glew.h>
#include <iostream>
#include <vector>

namespace Shaders {

	Shader::Shader()
		:mType(GL_NONE), mSourceCode(""), mName("")
	{
	}

	Shader::Shader(unsigned int type, std::string sourceCode, std::string name)
		:mType(type), mSourceCode(sourceCode), mName(name)
	{
		setup();
	}

	Shader::~Shader()
	{

	}

	void Shader::setup()
	{
		mID = glCreateShader(mType);
		compile();
	}

	void Shader::compile()
	{
		std::cout << "Compiling Shader: " << mName << std::endl;
		const char* sourcePointer = mSourceCode.c_str();
		glShaderSource(mID, 1, &sourcePointer, NULL);
		glCompileShader(mID);

		int compileResult = GL_FALSE;
		glGetShaderiv(mID, GL_COMPILE_STATUS, &compileResult);

		int compileLogLength = 0;
		glGetShaderiv(mID, GL_INFO_LOG_LENGTH, &compileLogLength);
		if (compileLogLength > 0) {
			std::vector<char> shaderErrors(compileLogLength + 1);
			glGetShaderInfoLog(mID, compileLogLength, NULL, &shaderErrors[0]);
			std::cout << "Shader: " << mName << " Failed to compile with error: \n\t" << shaderErrors[0] << std::endl;
		}
	}
}
