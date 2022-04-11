#pragma once
#include <glm/glm.hpp>
#include <map>
#include <string>
#include "Engine/Engine.h"
#define _CRT_SECURE_NO_WARNINGS
#include "Dependencies/stbi_image_write.h"
#include <ft2build.h>
#include FT_FREETYPE_H

struct Character {
    unsigned int TextureID;
    glm::ivec2   Size;
    glm::ivec2   Bearing;
    unsigned int Advance;
};

class TextRenderer
{
public:
    static void Load(std::string font, unsigned int fontSize);
    static void RenderText(std::string text, float x, float y, float scale, glm::vec3 color = glm::vec3(1.0f));
    static int GetStringSize(std::string text);
private:
    static void Init(unsigned int width, unsigned int height);
    friend class Renderer;
private:
    struct TextRendererData {
        unsigned int m_VAO, m_VBO;
        std::map<char, Character> Characters;
        Shader m_Shader;
        unsigned int m_ColorPtr = 0;
        unsigned int m_ProjectionPtr = 0;
        unsigned int m_Width, m_Height;
    };
    static TextRendererData s_Data;
};