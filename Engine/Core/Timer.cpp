#include "Timer.h"

constexpr float MAX_DELTA = 0.2f; // 디버깅용 최대 허용 프레임 시간

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
        m_DeltaTime = 0.0f; // 디버깅 중 브레이크포인트 무시
    }
#else
    m_DeltaTime = delta;
    m_ElapsedTime += delta;
#endif

    // delta가 유효한 경우에만 프레임 카운트 증가
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
