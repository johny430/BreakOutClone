#include "Texture.h"
#include "iostream"

void Texture::Generate(int width, int height, unsigned int num_channels)
{
    m_Width = width;
    m_Height = height;
    glGenTextures(1, &m_ID);
    m_Format = GL_RED;
    if (num_channels == 1)
        m_Format = GL_RED;
    else if (num_channels == 3)
        m_Format = GL_RGB;
    else if (num_channels == 4)
        m_Format = GL_RGBA;
    glBindTexture(GL_TEXTURE_2D, m_ID);
    glTexImage2D(GL_TEXTURE_2D, 0, m_Format, width, height, 0, m_Format, GL_UNSIGNED_BYTE, nullptr);
    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void Texture::Generate(int width, int height, unsigned int num_channels, const unsigned char* data)
{
    m_Width = width;
    m_Height = height;
    glGenTextures(1, &m_ID);
    m_Format = GL_RED;
    if (num_channels == 1)
        m_Format = GL_RED;
    else if (num_channels == 3)
        m_Format = GL_RGB;
    else if (num_channels == 4)
        m_Format = GL_RGBA;
    glBindTexture(GL_TEXTURE_2D, m_ID);
    glTexImage2D(GL_TEXTURE_2D, 0, m_Format, width, height, 0, m_Format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

Texture::~Texture()
{
    std::cout << "Destroy Texture" << std::endl;
}

void Texture::Bind() const
{
    glBindTexture(GL_TEXTURE_2D, m_ID);
}

void Texture::Bind(int slot) const
{
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, m_ID);
}
