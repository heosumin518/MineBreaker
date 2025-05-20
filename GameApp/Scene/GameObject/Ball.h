#pragma once
#include "../Engine/Scene/GameObject.h"
#include "../Engine/Physic/CircleCollider.h"

enum class BallType
{
	Normal,
	Flag
};

enum class BallState
{
	Ready,	// 발사 준비
	Flying	// 발사됨
};

class Ball : public GameObject
{
public:
	Ball(const glm::vec2& startPos, float radius);

	void Update(float deltaTime) override;
	void Render() override;

	void Reflect(const glm::vec2& normal);

	void ResetToWall(const glm::vec2& center, float radius, float angleRad);
	void MoveAlongWall(float deltaAngle, const glm::vec2& center, float wallRadius);
	void FireTowardsMouse(const glm::vec2& mouseWorldPos, float speed = 250.0f);

	ICollider* GetCollider() { return &m_Collider; }
	BallState GetState() const { return m_State; }
	float GetAimAngleRad() const { return m_AimAngleRad; }
	BallType GetType() const { return m_Type; }
	glm::vec2 GetPrevPos() const { return m_PrevPos; }

	void SetAimAngleRad(float rad) { m_AimAngleRad = rad; }
	void SetType(BallType type) { m_Type = type; }
	void SetWallCenter(const glm::vec2& center) { m_WallCenter = center; }

private:
	CircleCollider m_Collider;
	glm::vec2 m_Velocity;
	float m_Radius;
	BallState m_State;
	BallType m_Type;
	float m_AimAngleRad = glm::radians(-90.f);	// 시작 각도
	glm::vec2 m_PrevPos;
	glm::vec2 m_FireDir;

	glm::vec2 m_WallCenter;
};
