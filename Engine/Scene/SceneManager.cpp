#include "SceneManager.h"
#include "pch.h"
#include "glad/glad.h"
#include "Renderer/FontRenderer.h"

SceneManager::SceneManager()
	: m_CurrentScene(nullptr)
{
}

void SceneManager::Update(float deltaTime)
{
	m_CurrentScene->Update(deltaTime);
}

void SceneManager::Render()
{
	m_CurrentScene->Render();
}

Scene* SceneManager::GetSceneByName(const std::string& name) const
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
