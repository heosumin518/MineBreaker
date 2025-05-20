#pragma once
#include "../Engine/Scene/GameObject.h"
#include "../Engine/Physic/AABBCollider.h"

enum class BrickType
{
	Normal,
	Mine,
	Flagged
};

class Brick : public GameObject
{
public:
	Brick(const glm::vec2& pos, const glm::vec2& size);
	Brick(const glm::vec2& pos, const glm::vec2& size, BrickType type);

	void Update(float deltaTime) override;
	void Render() override;

	ICollider* GetCollider() { return &m_Collider; }

private:
	AABBCollider m_Collider;
	BrickType m_Type;
	glm::vec2 m_Size;
};

