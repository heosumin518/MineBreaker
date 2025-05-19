#include "CircleWall.h"

#include <iostream>
#include <ostream>

#include "glad/glad.h"

CircleWall::CircleWall(const glm::vec2& center, float radius)
	: m_Center(center)
	, m_Radius(radius)
	, m_Collider(center, radius)
{
}

void CircleWall::Update(float deltaTime)
{

}

void CircleWall::Render()
{
	const int segments = 64;
	float angleStep = 2.0f * glm::pi<float>() / segments;

	glColor3f(1.0f, 1.0f, 1.0f); // Èò»ö Å×µÎ¸®

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
