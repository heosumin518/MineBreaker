#include "GameObject.h"
#include "pch.h"

GameObject::GameObject()
	: m_Name("GameObject")
	, m_Transform(glm::mat4(1.0f))
	, m_Pos(0.0f, 0.0f)
	, m_Scale(1.0f, 1.0f)
	, m_Rotation(0.0f)
	, m_IsVisible(true)
	, m_Parent(nullptr)
{
}

void GameObject::UpdateTransform()
{
	// GLM�� Ʈ������ �Լ��� ���� ��� ���ʿ� ���ο� ����� ���ϴ� ���
	// matrix = T * R * S * I

	glm::mat4 local = glm::mat4(1.0f);	// ���� ��� ����
	local = glm::translate(m_Transform, glm::vec3(m_Pos, 0.0f));
	local = glm::rotate(m_Transform, m_Rotation, glm::vec3(0.0f, 0.0f, 1.0f));	// 2d �̹Ƿ� z���� �������� ȸ��
	local = glm::scale(m_Transform, glm::vec3(m_Scale, 1.0f));

	if (m_Parent)
		m_Transform = m_Parent->GetTransform() * local;
	else
		m_Transform = local;

	for (auto* child : m_Children)
		child->UpdateTransform();
}

void GameObject::AddChild(GameObject* child)
{
	child->SetParent(this);
	m_Children.push_back(child);
}
