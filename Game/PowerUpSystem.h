#pragma once
#include "PowerUp.h"
#include <vector>
#include "PowerUp.h"
#include "Engine/Engine.h"

class PowerUpSystem
{
public:
	PowerUpSystem(Ball& ball,Player& player);
	~PowerUpSystem();
	void Update(float delta_time);
	void Spawn(const glm::vec2& position);
	void CheckCollision();
	void Draw();
	void Reset();
private:
	Texture m_SpeedTexture;
	Texture m_StickyTexture;
	Texture m_IncreaseTexture;
	Texture m_PassTexture;
private:
	bool ShouldSpawn(unsigned int chance);
	bool IsPowerUpActive(PowerUpType type, int& index);
private:
	std::vector<PowerUp> m_PowerUps;
	Ball& m_CurrentBall;
	Player& m_CurrentPlayer;
};