#include "Ball.h"

#include "glad/glad.h"

Ball::Ball(const glm::vec2& startPos, float radius)
	: m_Collider(startPos, radius)
	, m_Velocity(glm::vec2(1.0f, 1.0f))
	, m_Radius(radius)
{
	SetPos(startPos);
	m_Velocity = glm::vec2(150.0f, 80.0f); // ���ϴ� ����� �ӵ� ����
}

void Ball::Update(float deltaTime)
{
	// �̵�
	glm::vec2 pos = m_Collider.GetCenter();
	pos += m_Velocity * deltaTime;
	m_Collider.SetCenter(pos);
	SetPos(pos);

	// �浹 �˻�

	// Ʈ������ ����
}

void Ball::Render()
{
	const int segments = 32;
	float angleStep = 2.0f * glm::pi<float>() / segments;

	glm::vec2 center = m_Collider.GetCenter();

	glColor3f(0.2f, 0.6f, 1.0f); // ���� �Ķ��� ��

	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(GetPos().x, GetPos().y); // �߽���

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
