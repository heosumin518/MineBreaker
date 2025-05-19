#pragma once
#include <string>
#include <vector>
#include "GameObject.h"

class Scene
{
public:
	Scene(const std::string& name);

	virtual void Update(float deltaTime) = 0;
	virtual void Render() = 0;

	std::string GetName() const { return m_Name; }
	GameObject* GetObjectByName(const std::string& name) const;

	void AddObject(GameObject* object);

protected:
	std::vector<GameObject*> m_Objects;

private:
	std::string m_Name;
};
