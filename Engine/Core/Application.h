#pragma once
#include "iostream"
#include "Window.h"
#include "Input.h"
#include "Time.h"
#include "Render/Renderer.h"
#include "Game/Game.h"

class Application
{
public:
	Application();
	~Application();
	int Run();
private:
	static void OnResize(GLFWwindow* window, int width, int height);
	static void OnKeyAction(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void OnMouseMove(GLFWwindow* window, double x, double y);
private:
	Window m_Window;
	Game m_Game;
};