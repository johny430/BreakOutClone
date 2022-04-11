#include "ParticleSystem.h"

ParticleSystem::ParticleSystem(int widht, int height, const Ball& ball)
{
    srand(time(0));
    unsigned int VBO, EBO;
    float vertices[] = {
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
    };
    unsigned int indices[] = {
        0,1,2,
        0,3,1
    };
    glGenVertexArrays(1, &this->m_Vao);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(this->m_Vao);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    projection = glm::ortho(0.0f, static_cast<float>(widht), 0.0f, static_cast<float>(height));
    ResourceLoader::ShaderFromFile(m_Shader, "assets/shaders/particle.vert", "assets/shaders/particle.frag");
    m_ModelPtr = m_Shader.GetUniformID("offset");
    m_ProjectionPtr = m_Shader.GetUniformID("projection");
    m_AlphaPtr = m_Shader.GetUniformID("alpha");
    m_Particles.reserve(m_ParticlesCount);
    m_Positions.reserve(m_ParticlesCount);
    m_Alphas.reserve(m_ParticlesCount);
    for (unsigned int i = 0; i < m_ParticlesCount; i++)
    {
        RespawnParticle(m_Particles[i],ball);
    }
    m_RespawnTime = 1.0f / 120.0f;
}

ParticleSystem::~ParticleSystem()
{
}

void ParticleSystem::Update(float delta_time, const Ball& ball)
{
    m_TimePassed += delta_time;
    for (unsigned int i = 0; i < m_ParticlesCount; ++i)
    {
        Particle& p = m_Particles[i];
        p.lifetime -= delta_time;
        if (p.lifetime > 0.0f){
            p.position -= p.velocity * delta_time;
            p.alpha -= delta_time * 2.5f;
            m_Positions[i] = p.position;
            m_Alphas[i] = p.alpha;
        }
        else {
            if (m_TimePassed > m_RespawnTime)
            {
                RespawnParticle(p, ball);
                m_TimePassed -= m_RespawnTime;
            }
        }
    }
}

void ParticleSystem::Draw(Texture& texture)
{
    glBindVertexArray(this->m_Vao);
    m_Shader.Bind();
    glActiveTexture(GL_TEXTURE0);
    texture.Bind();
    m_Shader.SetVector2fArray(m_ModelPtr,m_ParticlesCount,m_Positions.data());
    m_Shader.SetFloatArray(m_AlphaPtr, m_ParticlesCount, m_Alphas.data());
    m_Shader.SetMatrix4(m_ProjectionPtr, projection);
    glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, m_ParticlesCount);
    glBindVertexArray(0);
}

inline void ParticleSystem::RespawnParticle(Particle& particle,const Ball& ball)
{
    float random = ((rand() % 100) - 50) / 10.0f;
    float rColor = 0.5f + ((rand() % 100) / 100.0f);
    particle.position = ball.Position + random + glm::vec2(ball.Radius / 2.0f);
    particle.alpha = 1.0f;
    particle.lifetime = 1.0f;
    particle.velocity = ball.Velocity * 0.1f;
}
