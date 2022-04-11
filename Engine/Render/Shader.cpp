#include "Shader.h"

void Shader::Generate(const char* vertex_shader_source, const  char* fragment_shader_source)
{
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertex_shader_source, NULL);
    glCompileShader(vertexShader);
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragment_shader_source, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    m_ID = glCreateProgram();
    glAttachShader(m_ID, vertexShader);
    glAttachShader(m_ID, fragmentShader);
    glLinkProgram(m_ID);
    glGetProgramiv(m_ID, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(m_ID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::Generate(const char* vertex_shader_source, const  char* fragment_shader_source, const char* geometry_shader_source)
{
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertex_shader_source, NULL);
    glCompileShader(vertexShader);
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragment_shader_source, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    unsigned int geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
    glShaderSource(geometryShader, 1, &geometry_shader_source, NULL);
    glCompileShader(geometryShader);
    glGetShaderiv(geometryShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::GEOMETRY::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    m_ID = glCreateProgram();
    glAttachShader(m_ID, vertexShader);
    glAttachShader(m_ID, fragmentShader);
    glAttachShader(m_ID, geometryShader);
    glLinkProgram(m_ID);
    glGetProgramiv(m_ID, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(m_ID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    glDeleteShader(geometryShader);
}

Shader::~Shader()
{
    std::cout << "Destroy Shader" << std::endl;
}

void Shader::Bind() const
{
    glUseProgram(m_ID);
}

void Shader::UnBind() const
{
    glUseProgram(0);
}

void Shader::SetFloat(unsigned int id, float value) const
{
    glUniform1f(id, value);
}

void Shader::SetFloatArray(unsigned int id, int lenght, float* data) const
{
    glUniform1fv(id, lenght, data);
}

void Shader::SetInteger(unsigned int id, int value) const
{
    glUniform1i(id, value);
}

void Shader::SetIntegerArray(unsigned int id, int lenght, int* data) const
{
    glUniform1iv(id, lenght, data);
}

void Shader::SetVector2f(unsigned int id, const glm::vec2& value) const
{
    glUniform2f(id, value.x, value.y);
}

void Shader::SetVector2fArray(unsigned int id, int size, const glm::vec2* data) const
{
    glUniform2fv(id, GLsizei(size), glm::value_ptr(data[0]));
}

void Shader::SetVector2fArray(unsigned int id, int size, float* data) const
{
    glUniform2fv(id, GLsizei(size), data);
}

void Shader::SetVector3f(unsigned int id, const glm::vec3& value) const
{
    glUniform3f(id, value.x, value.y, value.z);
}

void Shader::SetVector4f(unsigned int id, const glm::vec4& value) const
{
    glUniform4f(id, value.x, value.y, value.z, value.w);
}

void Shader::SetMatrix3(unsigned int id, const glm::mat3& matrix) const
{
    glUniformMatrix3fv(id, 1, false, glm::value_ptr(matrix));
}

void Shader::SetMatrix4(unsigned int id, const glm::mat4& matrix) const
{
    glUniformMatrix4fv(id, 1, false, glm::value_ptr(matrix));
}

void Shader::SetMatrix4Array(unsigned int id, int lenght, glm::mat4* data) const
{
    glUniformMatrix4fv(id, GLsizei(lenght), GL_FALSE, glm::value_ptr(data[0]));
}

unsigned int Shader::GetUniformID(const std::string& name) const
{
    return glGetUniformLocation(m_ID, name.c_str());
}
