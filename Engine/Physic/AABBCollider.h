#pragma once
#include "ICollider.h"

class AABBCollider : public ICollider
{
public:
	AABBCollider(const glm::vec2& pos, const glm::vec2& size);

	ColliderType GetType() const override { return ColliderType::AABB; }
	glm::vec2 GetCenter() const override { return glm::vec2(); }
	glm::vec2 GetMin() const { return m_Min; }
	glm::vec2 GetMax() const { return m_Max; }

	bool CheckCollision(const ICollider* other, glm::vec2& outNormal) const override;

private:
	glm::vec2 m_Min = glm::vec2();
	glm::vec2 m_Max = glm::vec2();
};

