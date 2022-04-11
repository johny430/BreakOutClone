#pragma once
#include "Engine/Engine.h"
#include "Ball.h"
#include "Player.h"
#include "GameLevel.h"
#include "ParticleSystem.h"
#include "PowerUpSystem.h"
#include "Engine/Render/TextRenderer.h"

class Game
{
public:
	Game(int width,int height);
	~Game();
	void Update();
private:
	void GameOver();
	void Win();
	void Reset();
	GameLevel m_Level;
	friend class GameLevel;
private:
	Player m_Player;
	Texture m_PlayerTexture;
	float m_PlayerLeftBorder, m_PlayerRightBorder;
	float m_PlayerSpeed;
private:
	Ball m_Ball;
	Texture m_BallTexture;
	float   m_BallLeftBorder, m_BallRightBorder;
	float   m_BallTopBorder , m_BallBottomBorder;
private:
	int m_Width, m_Height;
private:
	Texture m_ParticleTexture;
	ParticleSystem m_Particles;
	PowerUpSystem m_PowerUps;
private:
	enum class GameState {
		Menu = 0,
		Play = 1,
		Win = 2,
		GameOver = 3
	};
	GameState m_State = GameState::Menu;
	int m_LivesCount = 22223;
	float m_StateTimer = 0.0f;
	bool m_ShouldFollow = false;
};