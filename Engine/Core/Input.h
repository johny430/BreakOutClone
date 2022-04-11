#pragma once
#include <xmemory>
#include "glad/glad.h"
#include "GLFW/glfw3.h"

class Input
{
private:
	static void Init();
	static void Shutdown();
	static void Update();
public:
	static bool GetKey(unsigned int key);
	static bool GetKeyUp(unsigned int key);
	static bool GetKeyDown(unsigned int key);
	static float GetMouseX();
	static float GetMouseY();
private:
	static void KeyCallback(int key, int action);
	static void MouseMoveCallback(double x, double y);
private:
	struct InputData
	{
		unsigned int m_CurrentFrame = 1;
		bool         m_KeyPresses[1032];
		int          m_Frames[1032];
		double m_MouseX, m_MouseY;
	};
	static InputData s_Data;
	friend class Application;
};