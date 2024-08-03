#pragma once

#include "glad/glad.h"
#include <GLFW/glfw3.h>

class Window
{
public:
	Window(int width, int height);
	~Window();

	bool ShouldClose();
	void SwapBuffers();

private:
	GLFWwindow* m_window = nullptr;
	static void APIENTRY glDebugOutput(GLenum source, GLenum type, unsigned int id, GLenum severity,
		GLsizei length, const char* message, const void* userParam);
};

