#pragma once
#include "../Engine/Scene/GameObject.h"
#include "../Engine/Physic/CircleCollider.h"

class CircleWall : public GameObject
{
public:
	CircleWall(const glm::vec2& center, float radius);

	void Update(float deltaTime) override;
	void Render() override;

	const glm::vec2& GetCenter() const { return m_Center; }
	float GetRadius() const { return m_Radius; }
	CircleCollider& GetCollider() { return m_Collider; }

private:
	glm::vec2 m_Center;
	float m_Radius;

	CircleCollider m_Collider;
};

