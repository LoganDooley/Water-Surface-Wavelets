#include "Window.h"
#include <iostream>

Window::Window(int width, int height)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

	m_window = glfwCreateWindow(width, height, "Window", nullptr, nullptr);
	if (m_window == nullptr) {
		std::cerr << "Failed to create GLFW window" << std::endl;
	}
	glfwMakeContextCurrent(m_window);
}

Window::~Window()
{
	glfwDestroyWindow(m_window);

	glfwTerminate();
}

bool Window::ShouldClose()
{
	return glfwWindowShouldClose(m_window);
}

void Window::SwapBuffers()
{
	glfwSwapBuffers(m_window);
}
