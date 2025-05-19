#pragma once
#include "ICollider.h"
#include "AABBCollider.h"

class CircleCollider : public ICollider
{
public:
	CircleCollider(const glm::vec2& center, float radius);

	ColliderType GetType() const override { return ColliderType::Circle; }
	glm::vec2 GetCenter() const override { return m_Center; }
	float GetRadius() const { return m_Radius; }
	void SetCenter(const glm::vec2& center) override { m_Center = center; } 

	bool CheckCollision(const ICollider* other, glm::vec2& outNormal) const override;
	static bool CheckCircleCollision(const CircleCollider& a, const CircleCollider& b, glm::vec2& outNormal);
	static bool CheckCircleAABBCollision(const CircleCollider& circle, const AABBCollider& box, glm::vec2& outNormal);

private:
	glm::vec2 m_Center = glm::vec2();
	float m_Radius = 0.0f;
};
