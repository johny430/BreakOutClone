#pragma once
#include "glm.hpp"
#include "vector"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Ball.h"
#include "Engine/Engine.h"

struct Particle
{
	glm::vec2 position;
	glm::vec2 velocity;
	float lifetime;
	float alpha = 1.0f;
};

class ParticleSystem
{
public:
	ParticleSystem(int widht, int height,const Ball& ball);
	~ParticleSystem();
	void Update(float delta_time, const Ball& ball);
	void Draw(Texture& texture);
private:
	inline void RespawnParticle(Particle& particle,const Ball& ball);
	float m_TimePassed = 0.0f;
	float m_RespawnTime = 0.0f;
private:
	Shader m_Shader;
	unsigned int m_Vao;
	unsigned int m_ModelPtr = 0;
	unsigned int m_ProjectionPtr = 0;
	unsigned int m_AlphaPtr = 0;
	glm::mat4 projection = glm::mat4(1.0f);
private:
	std::vector<Particle> m_Particles;
	std::vector<glm::vec2> m_Positions;
	std::vector<float>     m_Alphas;
	unsigned int m_ParticlesCount = 500;
};