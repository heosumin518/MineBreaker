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
	// 충돌 처리
}

void Brick::Render()
{
    glm::vec2 pos = GetPos(); // 왼쪽 아래 꼭짓점 기준
    glm::vec2 size = m_Size;

    // 색 설정
    switch (m_Type)
    {
        case BrickType::Normal:
            glColor3f(0.6f, 0.6f, 0.6f); // 회색
            break;
        case BrickType::Mine:
            glColor3f(1.0f, 0.0f, 0.0f); // 빨간색
            break;
        case BrickType::Flagged:
            glColor3f(0.0f, 0.5f, 1.0f); // 파란색
            break;
    }

    // 사각형 그리기 (좌하단 기준)
    glBegin(GL_QUADS);
    glVertex2f(pos.x, pos.y);
    glVertex2f(pos.x + size.x, pos.y);
    glVertex2f(pos.x + size.x, pos.y + size.y);
    glVertex2f(pos.x, pos.y + size.y);
    glEnd();

    //// 테두리 라인
    //glColor3f(0.1f, 0.1f, 0.1f); // 어두운 선
    //glBegin(GL_LINE_LOOP);
    //glVertex2f(pos.x, pos.y);
    //glVertex2f(pos.x + m_Size.x, pos.y);
    //glVertex2f(pos.x + m_Size.x, pos.y + m_Size.y);
    //glVertex2f(pos.x, pos.y + m_Size.y);
    //glEnd();
}
