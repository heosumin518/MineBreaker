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
	CircleWall* wall = new CircleWall({ 400.0f, 300.0f }, 250.0f);
	wall->SetName("Wall");
	AddObject(wall);

	Ball* ball = new Ball({ 400.0f, 300.0f}, 10.0f);
	ball->SetName("Ball");
	AddObject(ball);
}

void FirstStage::Update(float deltaTime)
{
	// 충돌 검사?
}

void FirstStage::Render()
{
	for (auto* object : m_Objects)
	{
		object->Render();
	}
}
