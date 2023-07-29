#include "Program.h"
#include <stdexcept>

namespace Shaders {
	Program::Program(std::string filePath)
		:mFilePath(filePath)
	{
		initialize();
	}

	Program::~Program()
	{

	}

	bool Program::initialize()
	{
		std::ifstream fileStream(mFilePath.c_str(), std::ios::in);
		if (!fileStream.is_open()) {
			std::cout << "Failed to open shader: " << mFilePath << std::endl;
			return false;
		}

		std::string vertexShaderSource;
		std::string fragmentShaderSource;

		std::string currentLine;
		bool addSourceToVertexShader = true;
		bool addSourceToFragmentShader = true;
		while (std::getline(fileStream, currentLine)) {
			
			bool currentLineIsDelimiter = currentLine.compare("#VERTEX_SHADER") == 0 || currentLine.compare("#FRAGMENT_SHADER") == 0;

			if (currentLine.compare("#VERTEX_SHADER") == 0) {
				addSourceToVertexShader = true;
				addSourceToFragmentShader = false;
			}

			if (currentLine.compare("#FRAGMENT_SHADER") == 0) {
				addSourceToVertexShader = false;
				addSourceToFragmentShader = true;
			}

			currentLine += "\n";
			if (addSourceToVertexShader && !currentLineIsDelimiter) {
				vertexShaderSource += currentLine;
			}

			if (addSourceToFragmentShader && !currentLineIsDelimiter) {
				fragmentShaderSource += currentLine;
			}
			
		}
		fileStream.close();

		mVertexShader = Shader(GL_VERTEX_SHADER, vertexShaderSource, "Test Vertex Shader");
		mFragmentShader = Shader(GL_FRAGMENT_SHADER, fragmentShaderSource, "Test Fragment Shader");

		link();

		glDeleteShader(mVertexShader.getID());
		glDeleteShader(mFragmentShader.getID());


		return true;
	}

	void Program::link()
	{
		std::cout << "Linking Shaders: \n\t" << mVertexShader.getName() << "\n\t" << mFragmentShader.getName();

		mProgramID = glCreateProgram();
		glAttachShader(mProgramID, mVertexShader.getID());
		glAttachShader(mProgramID, mFragmentShader.getID());
		glLinkProgram(mProgramID);

		int linkStatus;
		int linkLogLength = 0;
		glGetProgramiv(mProgramID, GL_LINK_STATUS, &linkStatus);
		glGetProgramiv(mProgramID, GL_INFO_LOG_LENGTH, &linkLogLength);
		if (linkLogLength > 0) {
			std::vector<char> programErrorMessages(linkLogLength + 1);
			glGetProgramInfoLog(mProgramID, linkLogLength, NULL, &programErrorMessages[0]);
			std::cout << "Failed to link with error : \n\t" << programErrorMessages[0] << std::endl;
		}
	}

	void Program::enable()
	{
		glUseProgram(mProgramID);
	}

	void Program::disable()
	{
		glUseProgram(0);
	}

	int Program::getLocation(std::string name)
	{
		return glGetUniformLocation(mProgramID, name.c_str());
	}

	void Program::setUniform1f(std::string name, GLfloat v0)
	{
		glUniform1f(getLocation(name), v0);
	}

	void Program::setUniform2f(std::string name, glm::f32vec2 vec)
	{
		glUniform2f(getLocation(name), vec.x, vec.y);
	}

	void Program::setUniform3f(std::string name, glm::f32vec3 vec)
	{
		glUniform3f(getLocation(name), vec.x, vec.y, vec.z);
	}

	void Program::setUniform4f(std::string name, glm::f32vec4 vec)
	{
		glUniform4f(getLocation(name), vec.x, vec.y, vec.z, vec.w);
	}

	void Program::setUniform1i(std::string name, int v0)
	{
		glUniform1i(getLocation(name), v0);
	}

	void Program::setUniform2i(std::string name, glm::i32vec2 vec)
	{
		glUniform2i(getLocation(name), vec.x, vec.y);
	}

	void Program::setUniform3i(std::string name, glm::i32vec3 vec)
	{
		glUniform3i(getLocation(name), vec.x, vec.y, vec.z);
	}

	void Program::setUniform4i(std::string name, glm::i32vec4 vec)
	{
		glUniform4i(getLocation(name), vec.x, vec.y, vec.z, vec.w);
	}

	void Program::setUniform1ui(std::string name, GLuint v0)
	{
		glUniform1ui(getLocation(name), v0);
	}

	void Program::setUniform2ui(std::string name, glm::u32vec2 vec)
	{
		glUniform2ui(getLocation(name), vec.x, vec.y);
	}

	void Program::setUniform3ui(std::string name, glm::u32vec3 vec)
	{
		glUniform3ui(getLocation(name), vec.x, vec.y, vec.z);
	}

	void Program::setUniform4ui(std::string name, glm::u32vec4 vec)
	{
		glUniform4ui(getLocation(name), vec.x, vec.y, vec.z, vec.w);
	}

	void Program::setUniformMatrix2fv(std::string name, GLsizei count, GLboolean transpose, glm::mat2 mat)
	{
		glUniformMatrix2fv(getLocation(name), count, transpose, &mat[0][0]);
	}

	void Program::setUniformMatrix3fv(std::string name, GLsizei count, GLboolean transpose, glm::mat3 mat)
	{
		glUniformMatrix3fv(getLocation(name), count, transpose, &mat[0][0]);
	}

	void Program::setUniformMatrix4fv(std::string name, GLsizei count, GLboolean transpose, glm::mat4 mat)
	{
		glUniformMatrix4fv(getLocation(name), count, transpose, &mat[0][0]);
	}

	void Program::setUniformMatrix2x3fv(std::string name, GLsizei count, GLboolean transpose, glm::mat2x3 mat)
	{
		glUniformMatrix2x3fv(getLocation(name), count, transpose, &mat[0][0]);
	}

	void Program::setUniformMatrix3x2fv(std::string name, GLsizei count, GLboolean transpose, glm::mat3x2 mat)
	{
		glUniformMatrix3x2fv(getLocation(name), count, transpose, &mat[0][0]);
	}

	void Program::setUniformMatrix2x4fv(std::string name, GLsizei count, GLboolean transpose, glm::mat2x4 mat)
	{
		glUniformMatrix2x4fv(getLocation(name), count, transpose, &mat[0][0]);
	}

	void Program::setUniformMatrix4x2fv(std::string name, GLsizei count, GLboolean transpose, glm::mat4x2 mat)
	{
		glUniformMatrix4x2fv(getLocation(name), count, transpose, &mat[0][0]);
	}

	void Program::setUniformMatrix3x4fv(std::string name, GLsizei count, GLboolean transpose, glm::mat3x4 mat)
	{
		glUniformMatrix3x4fv(getLocation(name), count, transpose, &mat[0][0]);
	}

	void Program::setUniformMatrix4x3fv(std::string name, GLsizei count, GLboolean transpose, glm::mat4x3 mat)
	{
		glUniformMatrix4x3fv(getLocation(name), count, transpose, &mat[0][0]);
	}

}