#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "Utils/ResourceLoader.h"
#include "PostProcessor.h"
#include "Core/Time.h"
#include "TextRenderer.h"

class Renderer
{
private:
	static void Init(int width, int height);
	static void Shutdown();
	static void Clear();
	static void BeginScene();
	static void EndScene();
	static void Resize(int width, int height);
public:
	static void DrawSprite(Texture& texture,const glm::vec2& position,const glm::vec2 size,const glm::vec3& color);
private:
	struct RendererData
	{
		unsigned int m_VBO;
		unsigned int m_EBO;
		unsigned int m_VAO;
		glm::mat4    m_Projection;
		Shader       m_QuadShader;
		int			 m_ModelPtr;
		int			 m_ProjectionPtr;
		int			 m_ColorPtr;

	};
	static RendererData s_Data;
	friend class Application;
};