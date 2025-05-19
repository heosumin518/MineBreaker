#include "Scene.h"
#include "pch.h"

Scene::Scene(const std::string& name)
	: m_Name(name)
{
}

void Scene::Update(float deltaTime)
{
	for (auto* object : m_Objects)
	{
		object->Update(deltaTime);
	}
}

void Scene::Render()
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
