#include "Ball.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"

Ball::Ball(const glm::vec2& startPos, float radius)
	: m_Collider(startPos, radius)
	, m_Velocity(glm::vec2())
	, m_Radius(radius)
	, m_State(BallState::Ready)
	, m_Type(BallType::Normal)
	, m_FireDir(glm::vec2(0.0f))
{
	SetPos(startPos);
	m_Velocity = glm::vec2(150.0f, 80.0f);
}

// TODO: ���� �ʿ�.. Util.h���� ������ ���� ������ ��� ��Ŭ��� ���������� �ӽ�.
glm::vec2 GetMouseWorldPositions(GLFWwindow* window)
{
	double mouseX, mouseY;
	glfwGetCursorPos(window, &mouseX, &mouseY);

	int width, height;
	glfwGetWindowSize(window, &width, &height);

	// OpenGL�� 2D ��ǥ��� ���� ���ϴ��� (0,0)
	float worldX = static_cast<float>(mouseX);
	float worldY = static_cast<float>(height - mouseY); // Y�� ������

	return glm::vec2(worldX, worldY);
}

void Ball::Update(float deltaTime)
{
	if (m_State == BallState::Flying)
	{
		m_PrevPos = m_Collider.GetCenter();

		glm::vec2 pos = m_Collider.GetCenter();

		// �� �߽����� ������� �߷��� ����
		glm::vec2 gravityDir = glm::normalize(m_WallCenter - pos);

		float gravityStrength = 400.0f;
		m_Velocity += gravityDir * gravityStrength * deltaTime;

		//// �ӵ� ����
		const float maxSpeed = 600.0f;
		if (glm::length(m_Velocity) > maxSpeed)
			m_Velocity = glm::normalize(m_Velocity) * maxSpeed;

		// ��ġ ������Ʈ
		m_PrevPos = pos;
		glm::vec2 newPos = pos + m_Velocity * deltaTime;
		m_Collider.SetCenter(newPos);
		SetPos(newPos);
	}

	glm::vec2 ballPos = m_Collider.GetCenter();
	glm::vec2 direction = glm::normalize(GetMouseWorldPositions(glfwGetCurrentContext()) - ballPos);
	m_FireDir = direction;
}

void Ball::Render()
{
	const int segments = 32;
	float angleStep = 2.0f * glm::pi<float>() / segments;

	if (m_Type == BallType::Normal)
	{
		glColor3f(0.2f, 0.6f, 1.0f); // ���� �Ķ���
	}
	else if (m_Type == BallType::Flag)
	{
		glColor3f(0.0f, 0.8f, 0.0f); // �ʷϻ�
	}

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

	if (m_State == BallState::Flying)
		return; // �̹� �߻�� �ĸ� �� �׸�

	glm::vec2 pos = m_Collider.GetCenter();
	float length = 50.0f; // ���� ����

	glm::vec2 end = pos + m_FireDir * length;

	glBegin(GL_LINES);
	glColor3f(1.0f, 0.0f, 0.0f); // ������
	glVertex2f(pos.x, pos.y);
	glVertex2f(end.x, end.y);
	glEnd();
}

void Ball::Reflect(const glm::vec2& normal)
{
	m_Velocity = glm::reflect(m_Velocity, normal);
}

void Ball::ResetToWall(const glm::vec2& center, float wallRadius, float angleRad)
{
	float offset = 5.0f; // ���ֺ��� �̸�ŭ ���ʿ� ��ġ
	float radius = wallRadius - m_Radius - offset;

	m_AimAngleRad = angleRad;

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
	m_PrevPos = GetPos();

	glm::vec2 ballPos = m_Collider.GetCenter();
	glm::vec2 direction = glm::normalize(mouseWorldPos - ballPos);

	m_Velocity = direction * speed;
	m_FireDir = direction;
	m_State = BallState::Flying;
}
