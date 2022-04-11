#include "ResourceLoader.h"

void ResourceLoader::ShaderFromFile(Shader& shader, const std::string& vertex_path, const std::string fragment_path)
{
    std::string line, vertex_source, fragment_source;
    std::ifstream file(vertex_path);
    if (file.is_open())
    {
        while (getline(file, line))
        {
            vertex_source += line + "\n";
        }
        file.close();
    }
    else {
        std::cout << "vertex file not loaded" << std::endl;
    }
    line = "";
    std::ifstream file2(fragment_path);
    if (file2.is_open())
    {
        while (getline(file2, line))
        {
            fragment_source += line + "\n";
        }
        file2.close();
    }
    else {
        std::cout << "fragment file not loaded" << std::endl;
        exit(1);
    }
    shader.Generate(vertex_source.c_str(), fragment_source.c_str());
}

void ResourceLoader::ShaderFromFile(Shader& shader, const std::string& vertex_path, const std::string fragment_path, const std::string geometry_path)
{
    std::string line, vertex_source, fragment_source, geometry_source;
    std::ifstream file(vertex_path);
    if (file.is_open())
    {
        while (getline(file, line))
        {
            vertex_source += line + "\n";
        }
        file.close();
    }
    else {
        std::cout << "file not loaded" << std::endl;
    }
    std::ifstream file2(fragment_path);
    if (file2.is_open())
    {
        while (getline(file2, line))
        {
            fragment_source += line + "\n";
        }
        file2.close();
    }
    else {
        std::cout << "file not loaded" << std::endl;
    }
    std::ifstream file3(geometry_path);
    if (file3.is_open())
    {
        while (getline(file3, line))
        {
            geometry_source += line + "\n";
        }
        file3.close();
    }
    else {
        std::cout << "file not loaded" << std::endl;
    }
    shader.Generate(vertex_source.c_str(), fragment_source.c_str(), geometry_source.c_str());
}

void ResourceLoader::Texture2DFromImage(Texture& texture, const std::string& path)
{
    int width, height, nrChannels;
    unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
    if (!data)
    {
        std::cout << stbi_failure_reason() << std::endl;
        std::cout << "Failed to load texture" << std::endl;
        exit(1);
    }
    texture.Generate(width, height, nrChannels, data);
    stbi_image_free(data);
}
