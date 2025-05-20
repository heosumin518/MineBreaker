#include "Scene.h"
#include "pch.h"
#include "Renderer/FontRenderer.h"

Scene::Scene(const std::string& name, const std::shared_ptr<FontRenderer>& fontRenderer)
	: m_Name(name)
	, m_FontRenderer(fontRenderer)
{
}

GameObject* Scene::GetObjectByName(const std::string& name) const
{
	for (auto* object : m_Objects)
	{
		if (object->GetName() == name)
			return object;
	}

	return nullptr;
}

void Scene::AddObject(GameObject* object)
{
	m_Objects.push_back(object);
}
