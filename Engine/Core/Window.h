#pragma once
#include "glad/glad.h"
#include "GLFW/glfw3.h"

class Window
{
public:
	Window(int width, int height, const char* title);
	~Window();
	void Update();
	bool Active();
	static void SetCursorPos(double x, double y) {
		glfwSetCursorPos(m_NativeWindow,x,y);
	};
public:
	void setResizeCallback(GLFWwindowsizefun function);
	void setKeyActionCallback(GLFWkeyfun function);
	void setMouseMoveCallback(GLFWcursorposfun function);
	void setScrollCallback(GLFWscrollfun function);
private:
	static GLFWwindow* m_NativeWindow;
};