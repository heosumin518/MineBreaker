#pragma once
#include "../Engine/Scene/Scene.h"

class Brick;

class FirstStage : public Scene
{
public:
	FirstStage(const std::string& name);

	void Initialize();
	void Update(float deltaTime) override;
	void Render() override;

	void CreateBricks(const glm::vec2& wallCenter);

	void CheckCollisionBetweenBallAndWall(float deltaTime);
	void CheckCollisionBetweenBallAndBrick(float deltaTime);

private:
	uint32_t m_Life;
	std::vector<Brick*> m_Bricks;

	float m_PrevRadian;
};

