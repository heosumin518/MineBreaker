#pragma once
#include <vector>
#include "Scene.h"

class SceneManager
{
public:
	SceneManager();

	void Update(float deltaTime);
	void Render();

	Scene* GetSceneByName(const std::string& name) const;

	void AddScene(Scene* scene);
	void SetCurrentScene(Scene* scene) { m_CurrentScene = scene; }
	Scene* GetCurrentScene() const { return m_CurrentScene; }

private:
	Scene* m_CurrentScene;
	std::vector<Scene*> m_Scenes;
};

