#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <GL\glew.h>
#include "Shader.h"
#include <glm/glm.hpp>

namespace Shaders {
	class Program
	{
	public:
		Program(std::string filePath);
		~Program();

        void enable();
        void disable();

		inline unsigned int getID() { return mProgramID; }
		inline std::string getFilePath() { return mFilePath; }
		inline Shader getFragmentShader() { return mFragmentShader; }
		inline Shader getVertexShader() { return mVertexShader; }

		int getLocation(std::string name);
        void setUniform1f(std::string name, GLfloat v0);
        void setUniform2f(std::string name, glm::f32vec2 vec);
        void setUniform3f(std::string name, glm::f32vec3 vec);
        void setUniform4f(std::string name, glm::f32vec4 vec);
        void setUniform1i(std::string name, int v0);
        void setUniform2i(std::string name, glm::i32vec2 vec);
        void setUniform3i(std::string name, glm::i32vec3 vec);
        void setUniform4i(std::string name, glm::i32vec4 vec);
        void setUniform1ui(std::string name, GLuint v0);
        void setUniform2ui(std::string name, glm::u32vec2 vec);
        void setUniform3ui(std::string name, glm::u32vec3 vec);
        void setUniform4ui(std::string name, glm::u32vec4 vec);
        void setUniformMatrix2fv(std::string name, GLsizei count, GLboolean transpose, glm::mat2 mat);
        void setUniformMatrix3fv(std::string name, GLsizei count, GLboolean transpose, glm::mat3 mat);
        void setUniformMatrix4fv(std::string name, GLsizei count, GLboolean transpose, glm::mat4 mat);
        void setUniformMatrix2x3fv(std::string name, GLsizei count, GLboolean transpose, glm::mat2x3 mat);
        void setUniformMatrix3x2fv(std::string name, GLsizei count, GLboolean transpose, glm::mat3x2 mat);
        void setUniformMatrix2x4fv(std::string name, GLsizei count, GLboolean transpose, glm::mat2x4 mat);
        void setUniformMatrix4x2fv(std::string name, GLsizei count, GLboolean transpose, glm::mat4x2 mat);
        void setUniformMatrix3x4fv(std::string name, GLsizei count, GLboolean transpose, glm::mat3x4 mat);
        void setUniformMatrix4x3fv(std::string name, GLsizei count, GLboolean transpose, glm::mat4x3 mat);

	private:
		bool initialize();
		
		void link();

	private:
		unsigned int mProgramID;
		std::string mFilePath;
		Shader mFragmentShader;
		Shader mVertexShader;
	};
}


