#include "Application.h"
#include <iostream>
#include "ShaderLoader.h"
#include <vector>

Application::Application()
{
	m_window = std::make_unique<Window>(800, 600);

	InitializeOpenGL();
}

Application::~Application()
{
}

void Application::Run()
{
	while (!m_window->ShouldClose()) {
		Update();
		Render();

		m_window->SwapBuffers();
		glfwPollEvents();
	}
}

void Application::InitializeOpenGL()
{
	glClearColor(1.0, 0.5, 0.75, 1.0);

	m_profileBufferShader = ShaderLoader::CreateShaderProgram("Shaders/ProfileBuffer.comp");

	m_textureShader = ShaderLoader::CreateShaderProgram("Shaders/Texture.vert", "Shaders/Texture.frag");

	std::vector<GLfloat> fullscreenQuadData = {
		-1, 1, 0, 0, 1,
		-1, -1, 0, 0, 0,
		1, -1, 0, 1, 0,
		-1, 1, 0, 0, 1,
		1, -1, 0, 1, 0,
		1, 1, 0, 1, 1,
	};

	GLuint fullscreenVbo;
	glGenBuffers(1, &fullscreenVbo);
	glBindBuffer(GL_ARRAY_BUFFER, fullscreenVbo);
	glBufferData(GL_ARRAY_BUFFER, fullscreenQuadData.size() * sizeof(GLfloat), fullscreenQuadData.data(), GL_STATIC_DRAW);
	glGenVertexArrays(1, &m_fullscreenQuadVao);
	glBindVertexArray(m_fullscreenQuadVao);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	
	glGenTextures(1, &m_profileBufferTexture);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_profileBufferTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RG16F, 4096, 400, 0, GL_RG,
		GL_FLOAT, NULL);
}

void Application::Update()
{
	m_t = glfwGetTime();
	glUseProgram(m_profileBufferShader);
	glBindImageTexture(0, m_profileBufferTexture, 0, GL_FALSE, 0, GL_READ_WRITE, GL_RG16F);
	glUniform1d(1, m_t);
	glDispatchCompute(4096, 400, 1);
	glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);
}

void Application::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(m_textureShader);
	glBindVertexArray(m_fullscreenQuadVao);
	glUniform1i(glGetUniformLocation(m_textureShader, "tex"), 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_profileBufferTexture);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}
