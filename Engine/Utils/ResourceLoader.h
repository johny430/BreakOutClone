#pragma once
#include "Render/Shader.h"
#include "Render/Texture.h"
#include <string>

class ResourceLoader {
public:
	static void ShaderFromFile(Shader& shader,const std::string& vertex_path, const std::string fragment_path);
	static void ShaderFromFile(Shader& shader,const std::string& vertex_path, const std::string fragment_path, const std::string geometry_path);
	static void Texture2DFromImage(Texture& texture, const std::string& path);
};