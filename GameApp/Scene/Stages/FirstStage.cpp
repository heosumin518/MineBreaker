#include "FirstStage.h"
#include "../GameObject/CircleWall.h"
#include "../GameObject/Ball.h"
#include "GLFW/glfw3.h"

FirstStage::FirstStage(const std::string& name)
	: Scene(name)
{
	Initialize();
}

void FirstStage::Initialize()
{
	CircleWall* wall = new CircleWall({ 300.0f, 400.0f }, 250.0f);
	wall->SetName("Wall");
	AddObject(wall);

	Ball* ball = new Ball({ 300.0f, 400.0f}, 10.0f);
	ball->SetName("Ball");
	AddObject(ball);

	float angle = glm::radians(-90.0f); // �Ʒ� �ʿ��� �߻� ���
	ball->ResetToWall(wall->GetCenter(), wall->GetRadius(), angle);
}

glm::vec2 GetMouseWorldPosition(GLFWwindow* window)
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

void FirstStage::Update(float deltaTime)
{
	for (auto* object : m_Objects)
	{
		object->Update(deltaTime);
	}

	// �浹 �˻�
	Ball* ball = dynamic_cast<Ball*>(GetObjectByName("Ball"));
	CircleWall* wall = dynamic_cast<CircleWall*>(GetObjectByName("Wall"));

	if (ball && wall)
	{
		static bool spaceReleased = true;

		if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_SPACE) == GLFW_PRESS && spaceReleased)
		{
			if (ball->GetState() == BallState::Ready)
			{
				glm::vec2 mouseWorld = GetMouseWorldPosition(glfwGetCurrentContext());
				ball->FireTowardsMouse(mouseWorld);
			}
			else if (ball->GetState() == BallState::Flying)
			{
				float angle = glm::radians(-90.0f); // �� ����
				ball->ResetToWall(wall->GetCenter(), wall->GetRadius(), angle);
			}

			spaceReleased = false;
		}

		if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_SPACE) == GLFW_RELEASE)
		{
			spaceReleased = true;
		}

		if (ball->GetState() == BallState::Flying)
		{
			glm::vec2 normal;
			if (wall->GetCollider().CheckCollision(ball->GetCollider(), normal))
			{
				ball->Reflect(normal);

				// ...
			}

		}
		else if (ball->GetState() == BallState::Ready)
		{
			glm::vec2 wallCenter = wall->GetCenter();
			float wallRadius = wall->GetRadius();

			if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_A) == GLFW_PRESS)
				ball->MoveAlongWall(-deltaTime * 2.0f, wallCenter, wallRadius);

			if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_D) == GLFW_PRESS)
				ball->MoveAlongWall(deltaTime * 2.0f, wallCenter, wallRadius);
		}
	}
}

void FirstStage::Render()
{
	for (auto* object : m_Objects)
	{
		object->Render();
	}
}
