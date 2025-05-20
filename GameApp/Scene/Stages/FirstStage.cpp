#include "FirstStage.h"
#include "GLFW/glfw3.h"
#include "../GameObject/CircleWall.h"
#include "../GameObject/Ball.h"
#include "../GameObject/Brick.h"
#include "../Engine/Renderer/FontRenderer.h"

FirstStage::FirstStage(const std::string& name, const std::shared_ptr<FontRenderer>& fontRenderer)
	: Scene(name, fontRenderer)
	, m_Life(5)
{
	Initialize();
}

void FirstStage::Initialize()
{
	CircleWall* wall = new CircleWall({ 300.0f, 400.0f }, 250.0f);
	wall->SetName("Wall");
	AddObject(wall);

	Ball* ball = new Ball({ 300.0f, 400.0f }, 10.0f);
	ball->SetName("Ball");
	AddObject(ball);

	CreateBricks(wall->GetCenter());

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

	CheckCollisionBetweenBallAndWall(deltaTime);
	CheckCollisionBetweenBallAndBrick(deltaTime);
}

void FirstStage::Render()
{
	for (auto* object : m_Objects)
	{
		if (object->GetIsVisible())
			object->Render();
	}

	m_FontRenderer->RenderText("Hello STB!", 100, 100, Color{1.f, 1.f, 1.f, 1.f});
}

void FirstStage::CreateBricks(const glm::vec2& wallCenter)
{
	glm::vec2 brickSize = { 30.0f, 20.0f }; // ����, ����
	float spacing = 1.0f; // ����
	int cols = 10;
	int rows = 12;

	glm::vec2 boardSize = glm::vec2(cols * (brickSize.x + spacing), rows * (brickSize.y + spacing));

	// ������ ���ϴ� ������ ���
	glm::vec2 boardOrigin = wallCenter - boardSize * 0.5f;

	for (int row = 0; row < rows; ++row)
	{
		for (int col = 0; col < cols; ++col)
		{
			glm::vec2 pos = boardOrigin + glm::vec2(
				col * (brickSize.x + spacing),
				row * (brickSize.y + spacing)
			);

			Brick* brick = new Brick(pos, brickSize, BrickType::Mine);
			AddObject(brick);
			m_Bricks.push_back(brick);
		}
	}
}

void FirstStage::CheckCollisionBetweenBallAndWall(float deltaTime)
{
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
				m_PrevRadian = ball->GetAimAngleRad();
			}
			else if (ball->GetState() == BallState::Flying)
			{
				ball->ResetToWall(wall->GetCenter(), wall->GetRadius(), ball->GetAimAngleRad());
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

				// ���� ������ ��ġ�� �ǵ�����
				ball->GetCollider()->SetCenter(ball->GetPrevPos());
				ball->SetPos(ball->GetPrevPos());
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

void FirstStage::CheckCollisionBetweenBallAndBrick(float deltaTime)
{
	// �浹 �˻�
	Ball* ball = dynamic_cast<Ball*>(GetObjectByName("Ball"));

	if (ball)
	{
		if (ball->GetState() == BallState::Flying)
		{
			for (auto* brick : m_Bricks)
			{
				if (brick)
				{
					if (!brick->GetIsVisible())
						continue;

					glm::vec2 normal;
					if (ball->GetCollider()->CheckCollision(brick->GetCollider(), normal))
					{
						ball->Reflect(normal);

						// ���� ������ ��ġ�� �ǵ�����
						ball->GetCollider()->SetCenter(ball->GetPrevPos());
						ball->SetPos(ball->GetPrevPos());

						brick->SetIsVisible(false);

						break;	// �ѹ��� �ϳ��� �������� �浹�� �˻��Ѵ�.
					}
				}
			}
		}
	}
}
