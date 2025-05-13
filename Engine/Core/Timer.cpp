#include "Timer.h"

constexpr float MAX_DELTA = 0.2f; // ������ �ִ� ��� ������ �ð�

Timer::Timer()
{
    const auto now = Clock::now();
    m_StartTime = now;
    m_LastTime = now;
    m_DeltaTime = 0.0f;
    m_ElapsedTime = 0.0f;
    m_AccumulatedTime = 0.0f;
    m_FrameCount = 0;
    m_FPS = 0;
}

void Timer::OnUpdate()
{
    const auto now = Clock::now();
    float delta = std::chrono::duration<float>(now - m_LastTime).count();
    m_LastTime = now;

#ifdef _DEBUG
    if (delta > 0.0f && delta < MAX_DELTA)
    {
        m_DeltaTime = delta;
        m_ElapsedTime += delta;
    }
    else
    {
        m_DeltaTime = 0.0f; // ����� �� �극��ũ����Ʈ ����
    }
#else
    m_DeltaTime = delta;
    m_ElapsedTime += delta;
#endif

    // delta�� ��ȿ�� ��쿡�� ������ ī��Ʈ ����
    if (m_DeltaTime > 0.0f)
    {
        m_FrameCount++;
        m_AccumulatedTime += m_DeltaTime;

        if (m_AccumulatedTime >= 1.0f)
        {
            m_FPS = static_cast<int>(m_FrameCount / m_AccumulatedTime);
            m_FrameCount = 0;
            m_AccumulatedTime = 0.0f;
        }
    }
}
