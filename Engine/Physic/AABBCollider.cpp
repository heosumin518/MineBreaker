#include "AABBCollider.h"

AABBCollider::AABBCollider(const glm::vec2& pos, const glm::vec2& size)
	: m_Min(pos)
	, m_Max(pos + size)
{
}

bool AABBCollider::CheckCollision(const ICollider* other, glm::vec2& outNormal) const
{

	return false;
}
