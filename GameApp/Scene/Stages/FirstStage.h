#pragma once
#include "../Engine/Scene/Scene.h"

struct Cell
{
	bool isMine = false;
	int adjacentMines = 0;
};

class Brick;

class FirstStage : public Scene
{
public:
	FirstStage(const std::string& name, const std::shared_ptr<FontRenderer>& fontRenderer);

	void Initialize();
	void Update(float deltaTime) override;
	void Render() override;

	void CreateMineMap(int rows, int cols, int mineCount);
	void CreateBricks(const glm::vec2& wallCenter);

	void CheckCollisionBetweenBallAndWall(float deltaTime);
	void CheckCollisionBetweenBallAndBrick();

	void CheckBallType();

	void RenderUI();

private:
	int m_Life;
	uint32_t m_Score;
	std::vector<Brick*> m_Bricks;

	std::vector<std::vector<Cell>> m_MineMap;

	float m_PrevRadian;
};

