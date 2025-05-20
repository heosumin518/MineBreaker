#pragma once
#include <memory>
#include <vector>
#include "Scene.h"

class FontRenderer;

class SceneManager
{
public:
	SceneManager();

	void Update(float deltaTime);
	void Render();

	void AddScene(Scene* scene);

	Scene* GetSceneByName(const std::string& name) const;
	Scene* GetCurrentScene() const { return m_CurrentScene; }

	void SetCurrentScene(Scene* scene) { m_CurrentScene = scene; }

private:
	Scene* m_CurrentScene;
	std::vector<Scene*> m_Scenes;
};

