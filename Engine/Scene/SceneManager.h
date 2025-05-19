#pragma once
#include <vector>
#include "Scene.h"

class SceneManager
{
public:
	SceneManager();

	Scene* GetSceneByName(const std::string& name);

	void AddScene(Scene* scene);

private:
	std::vector<Scene*> m_Scenes;
};

