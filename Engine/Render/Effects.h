#pragma once
#include "PostProcessor.h"

class Effects
{
public:
	static void Play();
private:
	static void Update(float delta_time);
	static float m_Time;
	friend class Application;
};