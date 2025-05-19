#include "CircleWall.h"

#include <iostream>
#include <ostream>

#include "glad/glad.h"

CircleWall::CircleWall(const glm::vec2& center, float radius)
	: m_Collider(center, radius)
	, m_Center(center)
	, m_Radius(radius)
{
}

void CircleWall::Update(float deltaTime)
{
	// 충돌 검사

}

void CircleWall::Render()
{
	GLenum err = glGetError();
	if (err != GL_NO_ERROR)
		std::cout << "OpenGL ERROR: " << err << std::endl;

	const int segments = 64;
	float angleStep = 2.0f * glm::pi<float>() / segments;

	glColor3f(1.0f, 1.0f, 1.0f); // 흰색 테두리

	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < segments; ++i)
	{
		float angle = i * angleStep;
		float x = m_Center.x + cos(angle) * m_Radius;
		float y = m_Center.y + sin(angle) * m_Radius;
		glVertex2f(x, y);
	}
	glEnd();
}
