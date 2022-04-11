#include "Window.h"
#include "iostream"

GLFWwindow* Window::m_NativeWindow = nullptr;

Window::Window(int width, int height, const char* title)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    m_NativeWindow = glfwCreateWindow(width, height, title, NULL, NULL);
    if (m_NativeWindow == NULL)
    {
        glfwTerminate();
        exit(1);
    }
    glfwMakeContextCurrent(m_NativeWindow);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        exit(-1);
    }
}

Window::~Window()
{
}

void Window::Update()
{
	glfwSwapBuffers(m_NativeWindow);
	glfwPollEvents();
}

bool Window::Active()
{
    return !glfwWindowShouldClose(m_NativeWindow);
}

void Window::setResizeCallback(GLFWwindowsizefun function)
{
    glfwSetWindowSizeCallback(m_NativeWindow,function);
}

void Window::setKeyActionCallback(GLFWkeyfun function)
{
    glfwSetKeyCallback(m_NativeWindow, function);
}

void Window::setMouseMoveCallback(GLFWcursorposfun function)
{
    glfwSetCursorPosCallback(m_NativeWindow, function);
}

void Window::setScrollCallback(GLFWscrollfun function)
{
    glfwSetScrollCallback(m_NativeWindow,function);
}
