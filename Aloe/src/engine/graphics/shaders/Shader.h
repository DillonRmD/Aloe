#pragma once

#include <string>
#include <GL\glew.h>

namespace Shaders {
	class Shader
	{
	public:
		Shader();
		Shader(unsigned int type, std::string sourceCode, std::string name = "NO_NAME");
		~Shader();

		inline unsigned int getID() { return mID; }
		inline unsigned int getType() { return mType; }
		inline std::string getName() { return mName; }
		inline std::string getSourceCode() { return mSourceCode; }

	private:
		void setup();
		void compile();

	private:
		unsigned int mID;
		unsigned int mType;
		std::string mName;
		std::string mSourceCode;
	};
}
