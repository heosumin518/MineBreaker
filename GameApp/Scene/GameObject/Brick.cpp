#include "Brick.h"

#include "glad/glad.h"

Brick::Brick(const glm::vec2& pos, const glm::vec2& size)
    : m_Collider(pos, size)
    , m_Type(BrickType::Normal)
    , m_Size(size)
{
    SetPos(pos);
}

Brick::Brick(const glm::vec2& pos, const glm::vec2& size, BrickType type)
	: m_Collider(pos, size)
	, m_Type(type)
	, m_Size(size)
{
    SetPos(pos);
}

void Brick::Update(float deltaTime)
{
	// �浹 ó��
}

void Brick::Render()
{
    glm::vec2 pos = GetPos(); // ���� �Ʒ� ������ ����
    glm::vec2 size = m_Size;

    // �� ����
    switch (m_Type)
    {
        case BrickType::Normal:
            glColor3f(0.6f, 0.6f, 0.6f); // ȸ��
            break;
        case BrickType::Mine:
            glColor3f(1.0f, 0.0f, 0.0f); // ������
            break;
        case BrickType::Flagged:
            glColor3f(0.0f, 0.5f, 1.0f); // �Ķ���
            break;
    }

    // �簢�� �׸��� (���ϴ� ����)
    glBegin(GL_QUADS);
    glVertex2f(pos.x, pos.y);
    glVertex2f(pos.x + size.x, pos.y);
    glVertex2f(pos.x + size.x, pos.y + size.y);
    glVertex2f(pos.x, pos.y + size.y);
    glEnd();

    //// �׵θ� ����
    //glColor3f(0.1f, 0.1f, 0.1f); // ��ο� ��
    //glBegin(GL_LINE_LOOP);
    //glVertex2f(pos.x, pos.y);
    //glVertex2f(pos.x + m_Size.x, pos.y);
    //glVertex2f(pos.x + m_Size.x, pos.y + m_Size.y);
    //glVertex2f(pos.x, pos.y + m_Size.y);
    //glEnd();
}
