#pragma once
#include "../Engine/Scene/GameObject.h"
#include "../Engine/Physic/AABBCollider.h"

class Brick : public GameObject
{
public:
	Brick(const glm::vec2& pos, const glm::vec2& size);

	void Update(float deltaTime) override;
	void Render() override;

	AABBCollider& GetCollider() { return m_Collider; }

private:
	AABBCollider m_Collider;
};

