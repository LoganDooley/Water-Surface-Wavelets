#pragma once

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
};

