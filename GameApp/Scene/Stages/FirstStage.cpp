#include "FirstStage.h"
#include "../GameObject/CircleWall.h"
#include "../GameObject/Ball.h"

FirstStage::FirstStage(const std::string& name)
	: Scene(name)
{
	Initialize();
}

void FirstStage::Initialize()
{
	CircleWall* wall = new CircleWall({ 300.0f, 400.0f }, 250.0f);
	wall->SetName("Wall");
	AddObject(wall);

	Ball* ball = new Ball({ 300.0f, 400.0f}, 10.0f);
	ball->SetName("Ball");
	AddObject(ball);


}

void FirstStage::Update(float deltaTime)
{
	for (auto* object : m_Objects)
	{
		object->Update(deltaTime);
	}

	// 충돌 검사
	Ball* ball = dynamic_cast<Ball*>(GetObjectByName("Ball"));
	CircleWall* wall = dynamic_cast<CircleWall*>(GetObjectByName("Wall"));

	if (ball && wall)
	{
		glm::vec2 normal;
		if (wall->GetCollider().CheckCollision(ball->GetCollider(), normal))
		{
			ball->Reflect(normal);
		}
	}
}

void FirstStage::Render()
{
	for (auto* object : m_Objects)
	{
		object->Render();
	}
}
