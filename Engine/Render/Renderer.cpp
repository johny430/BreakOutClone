#include "Renderer.h"

Renderer::RendererData Renderer::s_Data = Renderer::RendererData();

void Renderer::Init(int width, int height)
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    float vertices[] = {
        // pos      // tex
        -0.5f, 0.5f, 0.0f, 1.0f,
        0.5f, -0.5f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.0f, 0.0f,
        0.5f, 0.5f, 1.0f, 1.0f,
    };

    unsigned int indices[] = {
        0,1,2,
        0,3,1
    };

    glGenVertexArrays(1, &s_Data.m_VAO);
    glGenBuffers(1, &s_Data.m_VBO);
    glGenBuffers(1, &s_Data.m_EBO);

    glBindVertexArray(s_Data.m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, s_Data.m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s_Data.m_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    ResourceLoader::ShaderFromFile(s_Data.m_QuadShader,"assets/shaders/tile.vert", "assets/shaders/tile.frag");
    s_Data.m_Projection = glm::ortho(0.0f, static_cast<float>(width), 0.0f, static_cast<float>(height));
    s_Data.m_ModelPtr = s_Data.m_QuadShader.GetUniformID("model");
    s_Data.m_ProjectionPtr = s_Data.m_QuadShader.GetUniformID("projection");
    s_Data.m_ColorPtr = s_Data.m_QuadShader.GetUniformID("in_color");
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    PostProcessor::Init(width, height);
    TextRenderer::Init(width, height);
}

void Renderer::Shutdown()
{
}

void Renderer::Clear()
{
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::BeginScene()
{
    PostProcessor::BeginScene();
    glBindVertexArray(s_Data.m_VAO);
    s_Data.m_QuadShader.Bind();
}

void Renderer::EndScene()
{
    PostProcessor::EndScene();
    PostProcessor::Render(Time::GetTime());
}

void Renderer::Resize(int width, int height)
{
    s_Data.m_Projection = glm::ortho(0.0f, static_cast<float>(width), 0.0f, static_cast<float>(height));
    glViewport(0,0,width,height);
}

void Renderer::DrawSprite(Texture& texture, const glm::vec2& position, const glm::vec2 size, const glm::vec3& color = glm::vec3(1.0f))
{
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(position, 0.0f));
    model = glm::scale(model, glm::vec3(size, 1.0f));
    s_Data.m_QuadShader.SetMatrix4(s_Data.m_ModelPtr, model);
    s_Data.m_QuadShader.SetMatrix4(s_Data.m_ProjectionPtr, s_Data.m_Projection);
    s_Data.m_QuadShader.SetVector3f(s_Data.m_ColorPtr, color);
    texture.Bind(0);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}