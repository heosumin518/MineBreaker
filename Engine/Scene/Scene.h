#pragma once
#include <string>
#include <vector>
#include "GameObject.h"

class Scene
{
public:
	Scene(const std::string& name);

	void Update();
	void Render();

	std::string GetName() const { return m_Name; }
	GameObject* GetObjectByName(const std::string& name) const;

private:
	std::string m_Name;
	std::vector<GameObject*> m_Objects;
};
