#include "Game.h"

constexpr glm::vec2 StartVelocity = glm::vec2(300.0f, 500.0f);

Game::Game(int width, int height) :
	m_Ball(glm::vec2(10.0f), StartVelocity, 30.0f),
	m_BallTopBorder(height - m_Ball.Radius), m_BallBottomBorder(m_Ball.Radius * 1.5f),
	m_BallLeftBorder(m_Ball.Radius), m_BallRightBorder(width - m_Ball.Radius),
	m_Player(glm::vec2(width / 2.0f, 30.0f), glm::vec2(200, 40)),
	m_PlayerLeftBorder(m_Player.Size.x / 2.0f), m_PlayerRightBorder((float)width - m_Player.Size.x / 2.0f),
	m_PlayerSpeed(500.0f),
	m_Level("assets/levels/main.txt", width, height, *this),
	m_Height(height), m_Width(width),
	m_Particles(width, height, m_Ball),
	m_PowerUps(m_Ball,m_Player)
{
	ResourceLoader::Texture2DFromImage(m_BallTexture,"assets/texture/awesomeface.png");
	ResourceLoader::Texture2DFromImage(m_PlayerTexture, "assets/texture/paddle.png");
	ResourceLoader::Texture2DFromImage(m_ParticleTexture, "assets/texture/particle.png");
	TextRenderer::Load("assets/fonts/OCRAEXT.TTF", 24);
	SoundPlayer::Play("assets/sound/breakout.mp3", true);
}

Game::~Game()
{
}

void Game::Update()
{
	if (Input::GetKey(GLFW_KEY_D))
	{
		m_Player.Move(glm::vec2(m_PlayerSpeed * Time::GetDelta(), 0.0f));
		if (m_Player.Position.x > m_PlayerRightBorder)
		{
			m_Player.Position.x = m_PlayerRightBorder;
		}
	}
	if (Input::GetKey(GLFW_KEY_A))
	{
		m_Player.Move(glm::vec2(-m_PlayerSpeed * Time::GetDelta(), 0.0f));
		if (m_Player.Position.x < m_PlayerLeftBorder)
		{
			m_Player.Position.x = m_PlayerLeftBorder;
		}
	}
	if (m_State == GameState::Menu)
	{
		m_Ball.Follow(m_Player);
		if (Input::GetKey(GLFW_KEY_ENTER))
		{
			m_State = GameState::Play;
		}
	}
	else if (m_State == GameState::Play) {
		if (m_ShouldFollow)
		{
			m_Ball.Follow(m_Player);
			if (Input::GetKey(GLFW_KEY_ENTER))
			{
				m_ShouldFollow = false;
			}
		}
		else {
			m_Ball.Move(Time::GetDelta());
		}
		m_Particles.Update(Time::GetDelta(), m_Ball);
		m_PowerUps.Update(Time::GetDelta());
		if (m_Ball.Position.y >= m_BallTopBorder)
		{
			m_Ball.Position.y = m_BallTopBorder;
			m_Ball.Velocity.y = -m_Ball.Velocity.y;
		}
		else if (m_Ball.Position.y <= m_BallBottomBorder)
		{
			m_Ball.Position.y = m_BallBottomBorder;
			m_Ball.Velocity.y = -m_Ball.Velocity.y;
			Reset();
		}
		else if (m_Ball.Position.x >= m_BallRightBorder)
		{
			m_Ball.Position.x = m_BallRightBorder;
			m_Ball.Velocity.x = -m_Ball.Velocity.x;
		}
		else if (m_Ball.Position.x <= m_BallLeftBorder)
		{
			m_Ball.Position.x = m_BallLeftBorder;
			m_Ball.Velocity.x = -m_Ball.Velocity.x;
		}
		HitData hit;
		for (auto& brick : m_Level.Bricks)
		{
			if (!brick.IsActive())
			{
				continue;
			}
			if (Physics::CheckCollision(m_Ball, brick, hit))
			{
				if (brick.IsSolid())
				{
					if (hit.Direction == HitDirection::Horizontal)
					{
						m_Ball.Velocity.x = -m_Ball.Velocity.x;
					}
					else if (hit.Direction == HitDirection::Verical)
					{
						m_Ball.Velocity.y = -m_Ball.Velocity.y;
					}
					else
					{
						m_Ball.Velocity.x = -m_Ball.Velocity.x;
						m_Ball.Velocity.y = -m_Ball.Velocity.y;
					}
					Effects::Play();
				}
				else {
					if (!m_Ball.PassThrought)
					{
						if (hit.Direction == HitDirection::Horizontal)
						{
							m_Ball.Velocity.x = -m_Ball.Velocity.x;
						}
						else if (hit.Direction == HitDirection::Verical)
						{
							m_Ball.Velocity.y = -m_Ball.Velocity.y;
						}
						else
						{
							m_Ball.Velocity.x = -m_Ball.Velocity.x;
							m_Ball.Velocity.y = -m_Ball.Velocity.y;
						}
					}
					m_PowerUps.Spawn(brick.Position);
					m_Level.Destroy(brick);
					SoundPlayer::Play("assets/sound/bleep.mp3");
				}
			}
		}
		if (Physics::CheckCollision(m_Ball, m_Player, hit))
		{
			float distance = m_Ball.Position.x - m_Player.Position.x;
			float percentage = distance / m_Player.Size.x;
			float strength = 2.0f;
			glm::vec2 oldVelocity = m_Ball.Velocity;
			m_Ball.Velocity.x = StartVelocity.x * percentage * strength;
			m_Ball.Velocity = glm::normalize(m_Ball.Velocity) * glm::length(oldVelocity);
			m_Ball.Velocity.y = -1.0f * m_Ball.Velocity.y;
			if (m_Ball.Sticky)
			{
				m_Ball.Sticky = false;
				m_ShouldFollow = true;
			}
		}
		m_PowerUps.CheckCollision();
	}
	else if (m_State == GameState::Win)
	{
		m_StateTimer -= Time::GetDelta();
		if (m_StateTimer <= 0.0f)
		{
			m_State = GameState::Menu;
			m_StateTimer = 0.0f;
			m_Level.Reset();
			m_PowerUps.Reset();
		}
		m_Ball.Follow(m_Player);
	}
	else if (m_State == GameState::GameOver)
	{
		m_StateTimer -= Time::GetDelta();
		if (m_StateTimer <= 0.0f)
		{
			m_State = GameState::Play;
			m_StateTimer = 0.0f;
			m_Level.Reset();
			m_PowerUps.Reset();
		}
		m_Ball.Follow(m_Player);
	}
	Renderer::DrawSprite(m_PlayerTexture, m_Player.Position, m_Player.Size, glm::vec3(1.0f));
	Renderer::DrawSprite(m_BallTexture, m_Ball.Position, glm::vec2(m_Ball.Radius * 2.0f), glm::vec3(1.0f));
	m_PowerUps.Draw();
	m_Level.Draw();
	m_Particles.Draw(m_ParticleTexture);
	TextRenderer::RenderText("Lives: " + std::to_string(m_LivesCount), 0.0f, 0.0f, 1.0f, glm::vec3(1.0f));
	switch (m_State)
	{
	case Game::GameState::Menu: TextRenderer::RenderText("Press ENTER to start!", m_Width / 2.0f - 157.5f, m_Height / 2.0f, 1.0f, glm::vec3(1.0f));
		break;
	case Game::GameState::Win: TextRenderer::RenderText("You Won!", m_Width / 2.0f - 6.0f, m_Height / 2.0f, 1.0f, glm::vec3(0.0f, 0.0f, 1.0f));
		break;
	case Game::GameState::GameOver: TextRenderer::RenderText("Game Over!", m_Width / 2.0f - 75.0f, m_Height / 2.0f, 1.0f, glm::vec3(1.0f, 0.0f, 0.0f));
		break;
	}
}

void Game::GameOver()
{
	m_State = GameState::GameOver;
	m_StateTimer = 1.0f;
	m_ShouldFollow = true;
}

void Game::Win()
{
	m_State = GameState::Win;
	m_StateTimer = 1.0f;
	m_ShouldFollow = true;
}

void Game::Reset()
{
	if (m_LivesCount == 1)
	{
		GameOver();
		m_LivesCount = 3;
		return;
	}
	m_LivesCount--;
	m_Ball.Velocity = StartVelocity;
	m_Ball.Position.x = m_Player.Position.x;
	m_Ball.Position.y = m_Player.Position.y + m_Player.Size.y / 2.0f + m_Ball.Radius;
}
