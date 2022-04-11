#include "Input.h"

Input::InputData Input::s_Data = Input::InputData();

void Input::Init()
{
    memset(s_Data.m_KeyPresses, false, 1032 * sizeof(bool));
    memset(s_Data.m_Frames, 0, 1032 * sizeof(int));
}

void Input::Shutdown()
{
}

bool Input::GetKey(unsigned int key)
{
    return s_Data.m_KeyPresses[key];
}

bool Input::GetKeyUp(unsigned int key)
{
    return !s_Data.m_KeyPresses[key] && s_Data.m_Frames[key] == s_Data.m_CurrentFrame;
}

bool Input::GetKeyDown(unsigned int key)
{
    return s_Data.m_KeyPresses[key] && s_Data.m_Frames[key] == s_Data.m_CurrentFrame;
}

float Input::GetMouseX()
{
    return (float)s_Data.m_MouseX;
}

float Input::GetMouseY()
{
    return (float)s_Data.m_MouseY;
}

void Input::Update()
{
    s_Data.m_CurrentFrame++;
}

void Input::KeyCallback(int key,int action)
{
    if (action == GLFW_PRESS) {
        s_Data.m_KeyPresses[key] = true;
        s_Data.m_Frames[key] = s_Data.m_CurrentFrame;
    }
    else if (action == GLFW_RELEASE) {
        s_Data.m_KeyPresses[key] = false;
        s_Data.m_Frames[key] = s_Data.m_CurrentFrame;
    }
}

void Input::MouseMoveCallback(double x, double y)
{
    s_Data.m_MouseX = x;
    s_Data.m_MouseY = y;
}
