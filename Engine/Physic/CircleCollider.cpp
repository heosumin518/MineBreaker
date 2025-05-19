#include "CircleCollider.h"

#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/dual_quaternion.hpp"

CircleCollider::CircleCollider(const glm::vec2& center, float radius)
	: m_Center(center)
	, m_Radius(radius)
{
}

bool CircleCollider::CheckCollision(const ICollider* other, glm::vec2& outNormal) const
{
	if (other->GetType() == ColliderType::Circle)
	{
		auto* circle = dynamic_cast<const CircleCollider*>(other);
		return CheckCircleCollision(*this, *circle, outNormal);
	}
	else if (other->GetType() == ColliderType::AABB)
	{
		auto* box = dynamic_cast<const AABBCollider*>(other);
		return CheckCircleAABBCollision(*this, *box, outNormal);
	}

	return false;
}

bool CircleCollider::CheckCircleCollision(const CircleCollider& a, const CircleCollider& b, glm::vec2& outNormal)
{
	glm::vec2 diff = b.GetCenter() - a.GetCenter();
	float dist = glm::length(diff);
	float combined = a.GetRadius() + b.GetRadius();

	if (dist < combined) {
		outNormal = glm::normalize(diff);
		return true;
	}
	return false;
}

bool CircleCollider::CheckCircleAABBCollision(const CircleCollider& circle, const AABBCollider& box,
	glm::vec2& outNormal)
{
	glm::vec2 clamped = glm::clamp(circle.GetCenter(), box.GetMin(), box.GetMax());
	glm::vec2 diff = circle.GetCenter() - clamped;
	float dist2 = glm::dot(diff, diff);

	if (dist2 < circle.GetRadius() * circle.GetRadius()) {
		outNormal = glm::normalize(diff);
		return true;
	}
	return false;
}
