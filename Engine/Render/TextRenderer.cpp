#include "TextRenderer.h"

TextRenderer::TextRendererData TextRenderer::s_Data = TextRenderer::TextRendererData();

void TextRenderer::Init(unsigned int width, unsigned int height)
{
    s_Data.m_Width = width;
    s_Data.m_Height = height;
    ResourceLoader::ShaderFromFile(s_Data.m_Shader,"assets/shaders/text_2d.vert", "assets/shaders/text_2d.frag");
    glGenVertexArrays(1, &s_Data.m_VAO);
    glGenBuffers(1, &s_Data.m_VBO);
    glBindVertexArray(s_Data.m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, s_Data.m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    s_Data.m_ColorPtr = s_Data.m_Shader.GetUniformID("textColor");
    s_Data.m_ProjectionPtr = s_Data.m_Shader.GetUniformID("projection");
}

void TextRenderer::Load(std::string font, unsigned int fontSize)
{
    s_Data.Characters.clear();
    FT_Library ft;
    FT_Face face;
    if (FT_Init_FreeType(&ft)) {
        std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
    }
    if (FT_New_Face(ft, font.c_str(), 0, &face)) {
        std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
    }
    FT_Set_Pixel_Sizes(face, 0, fontSize);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    for (GLubyte c = 0; c < 128; c++)
    {
        if (FT_Load_Char(face, c, FT_LOAD_RENDER))
        {
            std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
            continue;
        }
        unsigned int texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, face->glyph->bitmap.width, face->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        Character character = {
            texture,
            glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
            glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
            (unsigned int)face->glyph->advance.x
        };
        s_Data.Characters.insert(std::pair<char, Character>(c, character));
    }
    glBindTexture(GL_TEXTURE_2D, 0);
    FT_Done_Face(face);
    FT_Done_FreeType(ft);
}

void TextRenderer::RenderText(std::string text, float x, float y, float scale, glm::vec3 color)
{
    s_Data.m_Shader.Bind();
    s_Data.m_Shader.SetVector3f(s_Data.m_ColorPtr, color);
    s_Data.m_Shader.SetMatrix4(s_Data.m_ProjectionPtr, glm::ortho(0.0f, static_cast<float>(s_Data.m_Width), static_cast<float>(s_Data.m_Height), 0.0f));
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(s_Data.m_VAO);
    std::string::const_iterator c;
    for (c = text.begin(); c != text.end(); c++)
    {
        Character ch = s_Data.Characters[*c];
        float xpos = x + ch.Bearing.x * scale;
        float ypos = y + (s_Data.Characters['H'].Bearing.y - ch.Bearing.y) * scale;
        float w = ch.Size.x * scale;
        float h = ch.Size.y * scale;
        float vertices[6][4] = {
            { xpos,     ypos + h,   0.0f, 1.0f },
            { xpos + w, ypos,       1.0f, 0.0f },
            { xpos,     ypos,       0.0f, 0.0f },

            { xpos,     ypos + h,   0.0f, 1.0f },
            { xpos + w, ypos + h,   1.0f, 1.0f },
            { xpos + w, ypos,       1.0f, 0.0f }
        };
        glBindTexture(GL_TEXTURE_2D, ch.TextureID);
        glBindBuffer(GL_ARRAY_BUFFER, s_Data.m_VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        x += (ch.Advance >> 6) * scale;
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

int TextRenderer::GetStringSize(std::string text)
{
    unsigned int offset = 0;
    std::string::const_iterator c;
    for (c = text.begin(); c != text.end(); c++)
    {
        offset += (s_Data.Characters[*c].Advance >> 6);
    }
    return offset;
}
