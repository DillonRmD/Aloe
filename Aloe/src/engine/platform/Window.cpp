#include "Window.h"


Window::Window(std::string title, uint32_t width, uint32_t height)
	:mTitle(title), mWidth(width), mHeight(height)
{
	setupGLFW();
	setupGLEW();
}

Window::~Window()
{
	glfwDestroyWindow(mWindowHandle);
	glfwTerminate();
}

void Window::setupGLFW()
{
	if (!glfwInit()) {
		throw std::runtime_error("Failed initializing GLFW Dependency");
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	mWindowHandle = glfwCreateWindow(mWidth, mHeight, mTitle.c_str(), nullptr, nullptr);
	if (!mWindowHandle) {
		throw std::runtime_error("Failed creating GLFW window handle");
	}

	glfwMakeContextCurrent(mWindowHandle);
}

void Window::setupGLEW()
{
	GLenum glewIntializationStatus = glewInit();
	if (glewIntializationStatus != GLEW_OK) {
		fprintf(stderr, "%s", glewGetErrorString(glewIntializationStatus));
		throw std::runtime_error("Failed to initialize GLEW");
	}
}

bool Window::isRunning()
{
	return !glfwWindowShouldClose(mWindowHandle);
}

void Window::update()
{
	glfwSwapBuffers(mWindowHandle);
	glfwPollEvents();
}

void Window::clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

glm::f64vec2 Window::getCursorPosition()
{
	double x, y;
	glfwGetCursorPos(mWindowHandle, &x, &y);

	return glm::f64vec2(x, y);
}

void Window::setWidth(uint32_t width)
{
	mWidth = width;
	glfwSetWindowSize(mWindowHandle, mWidth, mHeight);
}

void Window::setHeight(uint32_t height)
{
	mHeight = height;
	glfwSetWindowSize(mWindowHandle, mWidth, mHeight);
}

void Window::setSize(uint32_t width, uint32_t height)
{
	mWidth = width, mHeight = height;
	glfwSetWindowSize(mWindowHandle, mWidth, mHeight);
}

void Window::setSize(glm::uvec2 size)
{
	mWidth = size.x, mHeight = size.y;
	glfwSetWindowSize(mWindowHandle, mWidth, mHeight);
}

void Window::setTitle(std::string title)
{
	mTitle = title;
	glfwSetWindowTitle(mWindowHandle, mTitle.c_str());
}

