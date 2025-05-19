#pragma once
#include "glm/vec2.hpp"

enum class ColliderType
{
	None,
	Circle,
	AABB
};

class ICollider
{
public:
	virtual ColliderType GetType() const = 0;
	virtual bool CheckCollision(const ICollider* other, glm::vec2& outNormal) const = 0;
	virtual glm::vec2 GetCenter() const = 0;
	virtual void SetCenter(const glm::vec2& center) = 0;
};
