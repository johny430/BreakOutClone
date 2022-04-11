#include "PostProcessor.h"
#include "Renderer.h"

PostProcessor::PostProcessorData PostProcessor::s_Data = PostProcessor::PostProcessorData();

void PostProcessor::Init(int width, int height)
{
    unsigned int VBO;
    float vertices[] = {
        // pos        // tex
        -1.0f, -1.0f, 0.0f, 0.0f,
         1.0f,  1.0f, 1.0f, 1.0f,
        -1.0f,  1.0f, 0.0f, 1.0f,

        -1.0f, -1.0f, 0.0f, 0.0f,
         1.0f, -1.0f, 1.0f, 0.0f,
         1.0f,  1.0f, 1.0f, 1.0f
    };
    glGenVertexArrays(1, &s_Data.m_VAO);
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindVertexArray(s_Data.m_VAO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    ResourceLoader::ShaderFromFile(s_Data.m_Shader, "assets/shaders/post_processor.vert", "assets/shaders/post_processor.frag");
    s_Data.m_Texture.Generate(width, height, 3);
    s_Data.m_Width = width; 
    s_Data.m_Height = height;
    glGenFramebuffers(1, &s_Data.m_MSFBO);
    glGenFramebuffers(1, &s_Data.m_FBO);
    glGenRenderbuffers(1, &s_Data.m_RBO);
    glBindFramebuffer(GL_FRAMEBUFFER, s_Data.m_MSFBO);
    glBindRenderbuffer(GL_RENDERBUFFER, s_Data.m_RBO);
    glRenderbufferStorageMultisample(GL_RENDERBUFFER, 4, GL_RGB, width, height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, s_Data.m_RBO);
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "ERROR::POSTPROCESSOR: Failed to initialize MSFBO" << std::endl;
    glBindFramebuffer(GL_FRAMEBUFFER, s_Data.m_FBO);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, s_Data.m_Texture.GetID(), 0);
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "ERROR::POSTPROCESSOR: Failed to initialize FBO" << std::endl;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    s_Data.m_BlurPtr = s_Data.m_Shader.GetUniformID("blur_kernel");
    s_Data.m_OffsetsPtr = s_Data.m_Shader.GetUniformID("offsets");
    s_Data.m_ShakePtr = s_Data.m_Shader.GetUniformID("shake");
    s_Data.m_TimePtr = s_Data.m_Shader.GetUniformID("time");
}

void PostProcessor::Shutdown()
{
}

void PostProcessor::BeginScene()
{
    glBindFramebuffer(GL_FRAMEBUFFER, s_Data.m_MSFBO);
}

void PostProcessor::EndScene()
{
    glBindFramebuffer(GL_READ_FRAMEBUFFER, s_Data.m_MSFBO);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, s_Data.m_FBO);
    glBlitFramebuffer(0, 0, s_Data.m_Width, s_Data.m_Height, 0, 0, s_Data.m_Width, s_Data.m_Height, GL_COLOR_BUFFER_BIT, GL_NEAREST);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void PostProcessor::Render(float time)
{
    s_Data.m_Shader.Bind();
    s_Data.m_Shader.SetFloat(s_Data.m_TimePtr, time);
    s_Data.m_Shader.SetInteger(s_Data.m_ShakePtr, s_Data.m_Shake);
    s_Data.m_Shader.SetVector2fArray(s_Data.m_OffsetsPtr, 9, (float*)s_Data.m_Offsets);
    s_Data.m_Shader.SetFloatArray(s_Data.m_BlurPtr, 9, s_Data.m_BlurKernel);
    s_Data.m_Texture.Bind(0);
    glBindVertexArray(s_Data.m_VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}
