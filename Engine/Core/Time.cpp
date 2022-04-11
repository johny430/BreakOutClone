#include "Time.h"

float Time::m_CurrentFrame = 0.0f;
float Time::m_DeltaTime = 0.0f;
float Time::m_PreviousFrame = 0.0f;

float Time::GetDelta()
{
    return m_DeltaTime;
}

float Time::GetTime()
{
    return (float)glfwGetTime();
}

void Time::Update()
{
    m_CurrentFrame = (float)glfwGetTime();
    m_DeltaTime = m_CurrentFrame - m_PreviousFrame;
    m_PreviousFrame = m_CurrentFrame;
}
