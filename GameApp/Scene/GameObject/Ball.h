#pragma once
#include "../Engine/Scene/GameObject.h"
#include "../Engine/Physic/CircleCollider.h"

class Ball : public GameObject
{
public:
	Ball(const glm::vec2& startPos, float radius);

	void Update(float deltaTime) override;
	void Render() override;

	ICollider* GetCollider() { return &m_Collider; }

	void Reflect(const glm::vec2& normal);

private:
	CircleCollider m_Collider;
	glm::vec2 m_Velocity;

	float m_Radius;
};

