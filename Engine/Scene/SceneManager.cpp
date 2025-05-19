#include "SceneManager.h"
#include "pch.h"

SceneManager::SceneManager()
{
}

Scene* SceneManager::GetSceneByName(const std::string& name)
{
	for (auto* scene : m_Scenes)
	{
		if (scene->GetName() == name)
			return scene;
	}

	return nullptr;
}

void SceneManager::AddScene(Scene* scene)
{
	m_Scenes.push_back(scene);
}
