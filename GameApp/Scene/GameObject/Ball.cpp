#include "Ball.h"

#include "glad/glad.h"

Ball::Ball(const glm::vec2& startPos, float radius)
	: m_Collider(startPos, radius)
	, m_Velocity(glm::vec2())
	, m_Radius(radius)
	, m_State(BallState::Ready)
{
	SetPos(startPos);
	m_Velocity = glm::vec2(150.0f, 80.0f);
}

void Ball::Update(float deltaTime)
{
	if (m_State == BallState::Flying)
	{
		glm::vec2 pos = m_Collider.GetCenter();
		pos += m_Velocity * deltaTime;
		m_Collider.SetCenter(pos);
		SetPos(pos);
	}
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

void Ball::Reflect(const glm::vec2& normal)
{
	m_Velocity = glm::reflect(m_Velocity, normal);
}

void Ball::Fire(const glm::vec2& direction, float speed)
{
	m_Velocity = glm::normalize(direction) * speed;
	m_State = BallState::Flying;
}

void Ball::ResetToWall(const glm::vec2& center, float wallRadius, float angleRad)
{
	float offset = 5.0f; // 원주보다 이만큼 안쪽에 배치
	float radius = wallRadius - m_Radius - offset;

	glm::vec2 pos = center + glm::vec2(cos(angleRad), sin(angleRad)) * radius;

	m_Collider.SetCenter(pos);
	SetPos(pos);
	m_Velocity = glm::vec2(0.0f);
	m_State = BallState::Ready;
}

void Ball::MoveAlongWall(float deltaAngle, const glm::vec2& center, float wallRadius)
{
	m_AimAngleRad += deltaAngle;

	float offset = 5.0f;
	float radius = wallRadius - m_Radius - offset;

	glm::vec2 pos = center + glm::vec2(cos(m_AimAngleRad), sin(m_AimAngleRad)) * radius;

	m_Collider.SetCenter(pos);
	SetPos(pos);
}

void Ball::FireTowardsMouse(const glm::vec2& mouseWorldPos, float speed)
{
	glm::vec2 ballPos = m_Collider.GetCenter();
	glm::vec2 direction = glm::normalize(mouseWorldPos - ballPos);

	m_Velocity = direction * speed;
	m_State = BallState::Flying;
}
