#include "pch.h"
#include "Renderer.h"

#include "glad/glad.h"

Renderer::Renderer(uint32_t width, uint32_t height)
{
	SetViewport(0, 0, width, height);
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	Clear();
}

void Renderer::OnUpdate()
{
	Clear();
}

void Renderer::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
{
	glViewport(x, y, width, height);
}

void Renderer::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
