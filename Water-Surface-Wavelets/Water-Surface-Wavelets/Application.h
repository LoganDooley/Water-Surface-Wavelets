#pragma once

#include <memory>
#include "Window.h"

class Application
{
public:
	Application();
	~Application();

	void Run();

private:
	void InitializeOpenGL();
	void Update();
	void Render();

	GLuint m_profileBufferShader;
	GLuint m_profileBufferTexture;
	GLuint m_fullscreenQuadVao;
	GLuint m_textureShader;
	float m_t;

	std::unique_ptr<Window> m_window;
};
