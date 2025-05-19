#include "Brick.h"

Brick::Brick(const glm::vec2& pos, const glm::vec2& size)
	: m_Collider(pos, size)
{
}

void Brick::Update(float deltaTime)
{
	// 충돌 처리
}

void Brick::Render()
{
	
}
