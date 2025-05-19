#pragma once
#include "../Engine/Scene/Scene.h"

class FirstStage : public Scene
{
public:
	FirstStage(const std::string& name);

	void Initialize();
	void Update(float deltaTime) override;
	void Render() override;
};

