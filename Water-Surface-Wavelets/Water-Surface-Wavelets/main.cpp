#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "ShaderLoader.h"
#include "Application.h"

void SetOpenglDefaults() {
	glClearColor(1.0, 0.5, 0.75, 1.0);
}

void RunComputeShader() {
	glDispatchCompute(800, 600, 1);
	glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);
}

void Render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

int main() {
	Application app = Application();
	app.Run();

	return 0;
}