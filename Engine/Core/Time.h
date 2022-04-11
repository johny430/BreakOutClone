#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Time
{
public:
	static float GetDelta();
	static float GetTime();
private:
	static void Update();
private:
	static float m_CurrentFrame;
	static float m_PreviousFrame;
	static float m_DeltaTime;
	friend class Application;
};