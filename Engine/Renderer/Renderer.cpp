#include "pch.h"
#include "Renderer.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

Renderer::Renderer(uint32_t width, uint32_t height)
{
	SetViewport(0, 0, width, height);
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	Clear();
}

void PrintGLError(const char* location) {
	GLenum err = glGetError();
	if (err != GL_NO_ERROR)
		std::cout << "OpenGL ERROR (" << location << "): " << err << std::endl;
}

void Renderer::BeginRender(uint32_t width, uint32_t height)
{
	SetViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width, 0, height, -1, 1);  // 2D 좌표계 설정

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);  // 배경색
    Clear();  // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
}

void Renderer::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
{
	glViewport(x, y, width, height);
}

void Renderer::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
