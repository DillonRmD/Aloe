#pragma once

#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdexcept>
#include <glm/glm.hpp>

class Window
{
public:
	Window(std::string title, uint32_t width, uint32_t height);
	~Window();

	glm::f64vec2 getCursorPosition();

	inline uint32_t getWidth() { return mWidth; }
	inline uint32_t getHeight() { return mHeight; }
	inline std::string getTitle() { return mTitle; }

	void setWidth(uint32_t width);
	void setHeight(uint32_t height);
	void setSize(uint32_t width, uint32_t height);
	void setSize(glm::uvec2 size);
	void setTitle(std::string title);

	bool isRunning();
	void update();
	void clear();

private:
	void setupGLFW();
	void setupGLEW();

private:
	GLFWwindow* mWindowHandle;
	std::string mTitle;
	uint32_t mWidth;
	uint32_t mHeight;
};

