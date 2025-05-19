#include "Ball.h"

#include "glad/glad.h"

Ball::Ball(const glm::vec2& startPos, float radius)
	: m_Collider(startPos, radius)
	, m_Velocity(glm::vec2(1.0f, 1.0f))
	, m_Radius(radius)
{
	SetPos(startPos);
	m_Velocity = glm::vec2(150.0f, 80.0f); // 원하는 방향과 속도 설정
}

void Ball::Update(float deltaTime)
{
	// 이동
	glm::vec2 pos = m_Collider.GetCenter();
	pos += m_Velocity * deltaTime;
	m_Collider.SetCenter(pos);
	SetPos(pos);

	// 충돌 검사

	// 트랜스폼 갱신
}

void Ball::Render()
{
	const int segments = 32;
	float angleStep = 2.0f * glm::pi<float>() / segments;

	glm::vec2 center = m_Collider.GetCenter();

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

void Ball::Reflect(const glm::vec2& normal)
{
	m_Velocity = glm::reflect(m_Velocity, normal);
}
