#include "../engine/platform/Window.h"
#include "../engine/graphics/shaders/Program.h"
#include <glm/gtc/matrix_transform.hpp>

int main(int argc, char* argv[])
{
	Window window = Window("Aloe Engine", 800, 600);

	static const GLfloat vertices[] = {
   -1.0f, -1.0f, 0.0f,
   1.0f, -1.0f, 0.0f,
   0.0f,  1.0f, 0.0f,
	};

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	GLuint VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	Shaders::Program shaderProgram = Shaders::Program("E:\\dev\\Aloe\\build\\test.shader");

	glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)800 / (float)600, 0.1f, 100.0f);
	glm::mat4 view = glm::lookAt(
		glm::vec3(4, 3, 3),
		glm::vec3(0, 0, 0),
		glm::vec3(0, 1, 0)
	);

	glm::mat4 model = glm::mat4(1.0f);

	glm::mat4 mvp = projection * view * model;

	while (window.isRunning()) {
		window.clear();

		shaderProgram.enable();
		shaderProgram.setUniformMatrix4fv("MVP", 1, GL_FALSE, mvp);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glVertexAttribPointer(
			0,
			3,
			GL_FLOAT,
			GL_FALSE,
			0,
			0
		);
		
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glDisableVertexAttribArray(0);
		shaderProgram.disable();

		window.update();

		GLenum glError = glGetError();
		if (glError != GL_NO_ERROR) {
			std::string errorMessage((const char*)glewGetErrorString(glError));
			std::cout << "GL Error: " + errorMessage << std::endl;
		}
	}

	return 0;
}