#pragma once
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class GameObject
{
public:
	GameObject();
	~GameObject() = default;

	void Update(float deltaTime) {}
	void Render() {}

	std::string GetName() { return m_Name; }
	void SetName(const std::string& name) { m_Name = name; }

	bool GetIsVisible() const { return m_IsVisible; }
	void SetIsVisible(const bool isVisible) { m_IsVisible = isVisible; }

	void UpdateTransform();
	glm::mat4 GetTransform() const { return m_Transform; }
	void SetTransform(const glm::mat4& transform) { m_Transform = transform; }

	glm::vec2 GetPos() const { return m_Pos; }
	glm::vec2 GetScale() const { return m_Scale; }
	float GetRotation() const { return m_Rotation; }
	void SetPos(const glm::vec2& pos) { m_Pos = pos; }
	void SetScale(const glm::vec2& scale) { m_Scale = scale; }
	void SetRotation(const float rotation) { m_Rotation = rotation; }

	void AddChild(GameObject* child);
	void SetParent(GameObject* parent) { m_Parent = parent; }
	// TODO: Delete Children

private:
	std::string m_Name;

	glm::mat4 m_Transform;
	glm::vec2 m_Pos;
	glm::vec2 m_Scale;
	float m_Rotation;

	bool m_IsVisible;

	GameObject* m_Parent;
	std::vector<GameObject*> m_Children;
};
