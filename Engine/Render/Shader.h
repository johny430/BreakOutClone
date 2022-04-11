#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <glm/gtc/type_ptr.hpp>
#include <fstream>
#include <iostream>
#include "glm/glm.hpp"
#include <vector>

class Shader
{
public:
    Shader() {};
    void Generate(const char* vertex_shader_source, const  char* fragment_shader_source);
    void Generate(const char* vertex_shader_source, const  char* fragment_shader_source, const char* geometry_shader_source);
    ~Shader();
    void Bind() const;
    void UnBind() const;
    void SetFloat(unsigned int id, float value) const;
    void SetFloatArray(unsigned int id, int lenght, float* data) const;
    void SetInteger(unsigned int id, int value) const;
    void SetIntegerArray(unsigned int id, int lenght, int* data) const;
    void SetVector2f(unsigned int id, const glm::vec2& value) const;
    void SetVector2fArray(unsigned int id, int size, const glm::vec2* data) const;
    void SetVector2fArray(unsigned int id, int size, float* data) const;
    void SetVector3f(unsigned int id, const glm::vec3& value) const;
    void SetVector4f(unsigned int id, const glm::vec4& value) const;
    void SetMatrix3(unsigned int id, const glm::mat3& matrix) const;
    void SetMatrix4(unsigned int id, const glm::mat4& matrix) const;
    void SetMatrix4Array(unsigned int id, int lenght, glm::mat4* data) const;
    unsigned int GetUniformID(const std::string& name) const;
private:
    unsigned int m_ID = 0;
};