#include "Application.h"

Application::Application() :
    m_Window(1280, 720, "Main"),
    m_Game(1280,720)
{
    Input::Init();
    Renderer::Init(1280,720);
    m_Window.setResizeCallback(OnResize);
    m_Window.setMouseMoveCallback(OnMouseMove);
    m_Window.setKeyActionCallback(OnKeyAction);
}

Application::~Application()
{
    glfwTerminate();
    Input::Shutdown();
    Renderer::Shutdown();
}

int Application::Run()
{
    while (m_Window.Active())
    {
        Time::Update();
        Renderer::BeginScene();
        Renderer::Clear();
        m_Game.Update();
        Renderer::EndScene();
        Effects::Update(Time::GetDelta());
        Input::Update();
        m_Window.Update();
    }
    return 0;
}

void Application::OnResize(GLFWwindow* window, int width, int height)
{
    Renderer::Resize(width,height);
}

void Application::OnKeyAction(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    Input::KeyCallback(key,action);
}

void Application::OnMouseMove(GLFWwindow* window, double x, double y)
{
    Input::MouseMoveCallback(x,y);
}