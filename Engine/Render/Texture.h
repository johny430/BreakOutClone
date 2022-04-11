#pragma once
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <stb _image.h>

class Texture
{
public:
	Texture() {};
	void Generate(int width,int height,unsigned int num_channels);
	void Generate(int width, int height, unsigned int num_channels, const unsigned char* data);
	~Texture();

	void Bind() const;
	void Bind(int slot) const;
	inline unsigned int GetID() const { return m_ID; };
private:
	unsigned int m_ID = 0;
	unsigned int m_Format = 0;
	int m_Width = 0;
	int m_Height = 0;
};