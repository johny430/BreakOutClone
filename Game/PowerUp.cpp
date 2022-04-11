#include "PowerUp.h"

PowerUp::PowerUp(const glm::vec2& position, float duration, PowerUpType type)
	: Rectangle(position, glm::vec2(200.0f, 40.0f)), m_Duration(duration), m_Type(type)
{
}

void PowerUp::Update(float delta_time)
{
	m_Duration -= delta_time;
}

void PowerUp::Move(float delta_time)
{
	Position -= glm::vec2(0.f, 150.0f * delta_time);
}

void PowerUp::Activate(Ball& ball, Player& player)
{
	std::cout << "Activate" << std::endl;
	m_State = PowerUpState::Active;
	switch (m_Type)
	{
	case PowerUpType::Speed: ball.Velocity *= 2.0f;
		break;
	case PowerUpType::Sticky: ball.Sticky = true;
		break;
	case PowerUpType::PassThroug: ball.PassThrought = true;
		break;
	case PowerUpType::SizeUp: player.Size.x *= 1.2f;
		break;
	}
}

void PowerUp::Decativate(Ball& ball, Player& player)
{
	std::cout << "DeActivate" << std::endl;
	m_State = PowerUpState::Disabled;
	switch (m_Type)
	{
	case PowerUpType::Speed: ball.Velocity /= 2.0f;
		break;
	case PowerUpType::Sticky:ball.Sticky = false;
		break;
	case PowerUpType::PassThroug: ball.PassThrought = false;
		break;
	case PowerUpType::SizeUp: player.Size.x /= 1.2f;
		break;
	}
}
