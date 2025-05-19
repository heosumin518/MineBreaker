#include "Ball.h"

#include "glad/glad.h"

Ball::Ball(const glm::vec2& startPos, float radius)
	: m_Collider(startPos, radius)
	, m_Velocity(glm::vec2())
	, m_Radius(radius)
{
	SetPos(startPos);
}

void Ball::Update(float deltaTime)
{
	// 이동

	// 충돌 검사

	// 트랜스폼 갱신
}

void Ball::Render()
{
	const int segments = 32;
	float angleStep = 2.0f * glm::pi<float>() / segments;

	glColor3f(0.2f, 0.6f, 1.0f); // 밝은 파란색 공

	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(GetPos().x, GetPos().y); // 중심점

	for (int i = 0; i <= segments; ++i)
	{
		float angle = i * angleStep;
		float x = GetPos().x + cos(angle) * m_Radius;
		float y = GetPos().y + sin(angle) * m_Radius;
		glVertex2f(x, y);
	}
	glEnd();
}
