#pragma once
#include <chrono>

class Timer
{
public:
	Timer();

	void Update();

    float GetDeltaTime() const { return m_DeltaTime; }
    float GetElapsedTime() const { return m_ElapsedTime; }
    int GetFPS() const { return m_FPS; }

private:
    using Clock = std::chrono::high_resolution_clock;
    Clock::time_point m_StartTime;
    Clock::time_point m_LastTime;

    float m_DeltaTime = 0.0f;
    float m_ElapsedTime = 0.0f;

    // FPS °è»ê¿ë
    int m_FrameCount = 0;
    float m_AccumulatedTime = 0.0f;
    int m_FPS = 0;
};
