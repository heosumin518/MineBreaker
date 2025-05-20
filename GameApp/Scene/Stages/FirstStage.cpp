#include "FirstStage.h"
#include "../GameObject/CircleWall.h"
#include "../GameObject/Ball.h"
#include "../GameObject/Brick.h"
#include "../Engine/Core/Utils.h"
#include "../Engine/Renderer/FontRenderer.h"

FirstStage::FirstStage(const std::string& name, const std::shared_ptr<FontRenderer>& fontRenderer)
	: Scene(name, fontRenderer)
	, m_Life(5)
	, m_Score(0)
	, m_IsCleared(false)
{
	Initialize();
}

void FirstStage::Initialize()
{
	CircleWall* wall = new CircleWall({ 300.0f, 400.0f }, 250.0f);
	wall->SetName("Wall");
	AddObject(wall);

	CreateBricks(wall->GetCenter());

	Ball* ball = new Ball({ 300.0f, 400.0f }, 10.0f);
	ball->SetName("Ball");
	ball->SetWallCenter(wall->GetCenter());
	AddObject(ball);

	float angle = glm::radians(-90.0f); // �Ʒ� �ʿ��� �߻� ���
	ball->ResetToWall(wall->GetCenter(), wall->GetRadius(), angle);
}

void FirstStage::Update(float deltaTime)
{
	bool isGameOver = CheckIsDead();
	bool isGameClear = CheckIsClear();

	if (isGameOver || isGameClear)
		return;

	for (auto* object : m_Objects)
	{
		object->Update(deltaTime);
	}

	CheckCollisionBetweenBallAndWall(deltaTime);
	CheckCollisionBetweenBallAndBrick();
	CheckBallType();
}

void FirstStage::Render()
{
	m_IsCleared = true;

	for (auto* object : m_Objects)
	{
		if (object->GetIsVisible())
		{
			object->Render();
			
			if (object->GetName() == "Brick")
			{
				m_IsCleared = false;
			}
		}
		else
		{
			if (object->GetName() == "Brick")
			{
				Brick* brick = dynamic_cast<Brick*>(object);

				std::string number = std::to_string(brick->GetMineCount());
				float offsetX = 10.0f;
				float offsetY = 1.f;

				if (number == "0")
				{
					if (brick->GetType() == BrickType::Mine)
					{
						m_FontRenderer->RenderText("X", brick->GetPos().x + offsetX, brick->GetPos().y + offsetY, Color{ 1.0f, 0.0f, 0.0f, 1.0f });
					}
					else if (brick->GetType() == BrickType::Flagged)
					{
						m_FontRenderer->RenderText("O", brick->GetPos().x + offsetX - 2.0f, brick->GetPos().y + offsetY, Color{ 0.0f, 1.0f, 0.0f, 1.0f });
					}
					continue;
				}

				// ���� ���� ����
				Color color = Color{ 1.0f, 1.0f, 1.0f, 1.0f }; // �⺻ ���
				switch (brick->GetMineCount())
				{
					//case 1: color = Color{ 0.3f, 0.6f, 1.0f, 1.0f }; break; // ���Ķ���
					case 1: color = Color{ 1.0f, 1.0f, 1.0f, 1.0f }; break; // ���
					case 2: color = Color{ 1.0f, 0.5f, 0.0f, 1.0f }; break; // ��Ȳ��
						//case 2: color = Color{ 0.0f, 0.8f, 0.0f, 1.0f }; break; // �ʷϻ�
					case 3: color = Color{ 1.0f, 1.0f, 0.0f, 1.0f }; break; // �����
					case 4: color = Color{ 0.0f, 0.0f, 0.5f, 1.0f }; break; // ����
					case 5: color = Color{ 0.5f, 0.3f, 0.1f, 1.0f }; break; // ����
				}

				m_FontRenderer->RenderText(number.c_str(), brick->GetPos().x + offsetX, brick->GetPos().y + offsetY, color);
			}
		}
	}

	RenderUI();
}

void FirstStage::CreateMineMap(int rows, int cols, int mineCount)
{
	// ���ں��� �׵θ��� ���ڰ� ��ġ���� ���� �� ���� ���ں��带 ����
	while (true)
	{
		m_MineMap.assign(rows, std::vector<Cell>(cols)); // �ʱ�ȭ

		// ���� ��ġ
		int minesToPlace = mineCount;
		while (minesToPlace > 0) {
			int r = rand() % rows;
			int c = rand() % cols;

			// �׵θ��� ����
			if (r == 0 || r == rows - 1 || c == 0 || c == cols - 1)
				continue;

			if (!m_MineMap[r][c].isMine) {
				m_MineMap[r][c].isMine = true;
				--minesToPlace;
			}
		}

		// �׵θ��� ���ڰ� ������ Ȯ��
		bool hasMineOnEdge = false;
		for (int r = 0; r < rows; ++r) {
			for (int c = 0; c < cols; ++c) {
				if ((r == 0 || r == rows - 1 || c == 0 || c == cols - 1) && m_MineMap[r][c].isMine) {
					hasMineOnEdge = true;
					break;
				}
			}
			if (hasMineOnEdge) break;
		}

		if (!hasMineOnEdge)
			break; // ���� ��ġ �Ϸ�
	}

	// ���� ���
	for (int r = 0; r < rows; ++r) {
		for (int c = 0; c < cols; ++c) {
			if (m_MineMap[r][c].isMine)
				continue;

			int count = 0;
			for (int dr = -1; dr <= 1; ++dr) {
				for (int dc = -1; dc <= 1; ++dc) {
					int nr = r + dr, nc = c + dc;
					if (nr >= 0 && nr < rows && nc >= 0 && nc < cols &&
						m_MineMap[nr][nc].isMine)
						++count;
				}
			}
			m_MineMap[r][c].adjacentMines = count;
		}
	}
}

void FirstStage::CreateBricks(const glm::vec2& wallCenter)
{
	glm::vec2 brickSize = { 30.0f, 20.0f }; // ����, ����
	float spacing = 1.0f; // ����
	int cols = 10;
	int rows = 12;

	CreateMineMap(rows, cols, 10);

	glm::vec2 boardSize = glm::vec2(cols * (brickSize.x + spacing), rows * (brickSize.y + spacing));

	// ������ ���ϴ� ������ ���
	glm::vec2 boardOrigin = wallCenter - boardSize * 0.5f;

	for (int row = 0; row < rows; ++row)
	{
		for (int col = 0; col < cols; ++col)
		{
			// Y�� ������ ����
			glm::vec2 pos = boardOrigin + glm::vec2(
				col * (brickSize.x + spacing),
				(rows - 1 - row) * (brickSize.y + spacing)
			);

			const Cell& cell = m_MineMap[row][col];
			BrickType type = BrickType::Normal;

			if (cell.isMine) {
				type = BrickType::Mine;
			}

			Brick* brick = new Brick(pos, brickSize, type);
			brick->SetName("Brick");
			brick->SetMineCount(cell.adjacentMines);

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
				ball->FireTowardsMouse(mouseWorld, 150.0f);
				m_PrevRadian = ball->GetAimAngleRad();
			}
			else if (ball->GetState() == BallState::Flying)
			{
				glm::vec2 ballPos = ball->GetCollider()->GetCenter();
				glm::vec2 center = wall->GetCenter();
				glm::vec2 dir = glm::normalize(ballPos - center);
				float angleRad = atan2(dir.y, dir.x);

				ball->ResetToWall(center, wall->GetRadius(), angleRad);
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
			m_FontRenderer->RenderText("Press 'SPACE' to Fire", 195, 100, Color{ 1.f, 1.f, 1.f, 1.f });
			m_FontRenderer->RenderText("Use 'A' / 'D' to move along the wall", 128, 75, Color{ 1.f, 1.f, 1.f, 1.f });

			glm::vec2 wallCenter = wall->GetCenter();
			float wallRadius = wall->GetRadius();

			if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_A) == GLFW_PRESS)
				ball->MoveAlongWall(-deltaTime * 2.0f, wallCenter, wallRadius);

			if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_D) == GLFW_PRESS)
				ball->MoveAlongWall(deltaTime * 2.0f, wallCenter, wallRadius);
		}
	}
}

void FirstStage::CheckCollisionBetweenBallAndBrick()
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

						if (ball->GetType() == BallType::Flag)
						{
							// ���� ������ ��� ǥ�ø� �ߴٸ� ������ 5�� ��´�.
							if (brick->GetType() == BrickType::Mine)
							{
								brick->SetType(BrickType::Flagged);
								m_Score += 5;
							}
							// ���ڰ� �ƴ� ������ ��� ǥ�ø� �ߴٸ� ������ 2�� �Ҵ´�.
							else
							{
								m_Score -= 2;
							}
						}

						// ��� �� ���� ó��
						if (brick->GetType() == BrickType::Mine)
							m_Life -= 1;
						else if (brick->GetType() == BrickType::Normal)
							m_Score += 1;

						break;	// �ѹ��� �ϳ��� �������� �浹�� �˻��Ѵ�.
					}
				}
			}
		}
	}
}

void FirstStage::CheckBallType()
{
	static bool leftShiftReleased = true;

	Ball* ball = dynamic_cast<Ball*>(GetObjectByName("Ball"));

	if (ball == nullptr)
		return;

	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS && leftShiftReleased)
	{
		if (ball->GetType() == BallType::Normal)
			ball->SetType(BallType::Flag);
		else
			ball->SetType(BallType::Normal);

		leftShiftReleased = false;
	}

	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
	{
		leftShiftReleased = true;
	}
}

bool FirstStage::CheckIsDead()
{
	if (m_Life <= 0)
	{
		m_FontRenderer->RenderText("GAME OVER!!", 225, 700, Color{ 1.f, 1.f, 1.f, 1.f });

		return true;
	}

	return false;
}

bool FirstStage::CheckIsClear()
{
	if (m_IsCleared)
	{
		m_FontRenderer->RenderText("GAME CLEAR!!", 220, 700, Color{ 1.f, 1.f, 1.f, 1.f });

		return true;
	}

	return false;
}

void FirstStage::RenderUI()
{
	std::string text1 = "Life: " + std::to_string(m_Life);
	m_FontRenderer->RenderText(text1.c_str(), 80, 700, Color{ 1.f, 1.f, 1.f, 1.f });

	std::string text2 = "Score: " + std::to_string(m_Score);
	m_FontRenderer->RenderText(text2.c_str(), 440, 700, Color{ 1.f, 1.f, 1.f, 1.f });

	m_FontRenderer->RenderText("Press 'SHIFT' to swtich ball's type", 130, 50, Color{ 1.f, 1.f, 1.f, 1.f });
}
