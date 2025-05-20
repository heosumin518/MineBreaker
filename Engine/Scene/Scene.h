#pragma once
#include <memory>
#include <string>
#include <vector>
#include "GameObject.h"

class FontRenderer;

class Scene
{
public:
	Scene(const std::string& name, const std::shared_ptr<FontRenderer>& fontRenderer);

	virtual void Update(float deltaTime) = 0;
	virtual void Render() = 0;

	std::string GetName() const { return m_Name; }
	GameObject* GetObjectByName(const std::string& name) const;

	void AddObject(GameObject* object);

protected:
	std::vector<GameObject*> m_Objects;
	std::shared_ptr<FontRenderer> m_FontRenderer;

private:
	std::string m_Name;
};
