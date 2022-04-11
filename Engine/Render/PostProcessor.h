#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "Texture.h"
#include "Utils/ResourceLoader.h"

class PostProcessor
{
public:
	static void Init(int width, int height);
	static void Shutdown();
	static void BeginScene();
	static void EndScene();
	static void Render(float delta_time);
private:
	struct PostProcessorData
	{
		unsigned int m_MSFBO, m_FBO;
		unsigned int m_RBO;
		unsigned int m_VAO;
		Shader m_Shader;
		Texture m_Texture;
		unsigned int m_Width;
		unsigned int m_Height;

		unsigned int m_ShakePtr;
		unsigned int m_TimePtr;
		unsigned int m_OffsetsPtr;
		unsigned int m_BlurPtr;
		bool m_Shake = false;
		float m_BlurKernel[9] = {
		   1.0f / 16.0f, 2.0f / 16.0f, 1.0f / 16.0f,
		   2.0f / 16.0f, 4.0f / 16.0f, 2.0f / 16.0f,
		   1.0f / 16.0f, 2.0f / 16.0f, 1.0f / 16.0f
		};

		float m_Offsets[9][2] = {
			{ -(1.0f / 300.0f),  (1.0f / 300.0f)  },  // top-left
			{  0.0f,    (1.0f / 300.0f)  },  // top-center
			{  (1.0f / 300.0f),  (1.0f / 300.0f)  },  // top-right
			{ -(1.0f / 300.0f),  0.0f    },  // center-left
			{  0.0f,    0.0f    },  // center-center
			{  (1.0f / 300.0f),  0.0f    },  // center - right
			{ -(1.0f / 300.0f), -(1.0f / 300.0f)  },  // bottom-left
			{  0.0f,   -(1.0f / 300.0f)  },  // bottom-center
			{  (1.0f / 300.0f), -(1.0f / 300.0f)  }   // bottom-right    
		};
	};
	static PostProcessorData s_Data;
	friend class Application;
	friend class Effects;
};