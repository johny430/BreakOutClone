#include "Effects.h"

float Effects::m_Time = 0.0f;

void Effects::Play()
{
	PostProcessor::s_Data.m_Shake = true;
	m_Time = 0.3f;
}

void Effects::Update(float delta_time)
{
	if (PostProcessor::s_Data.m_Shake)
	{
		m_Time -= delta_time;
		if (m_Time <= 0.0f)
		{
			PostProcessor::s_Data.m_Shake = false;
			m_Time = 0.0f;
		}
	}
}
