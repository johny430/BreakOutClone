#pragma once
#include <glm/glm.hpp>
#include "Ball.h"
#include "Player.h"

enum class PowerUpType
{
	Speed = 0,
	Sticky = 1,
	PassThroug = 2,
	SizeUp = 3,
};

enum class PowerUpState {
	Falling = 0,
	Active = 1,
	Disabled = 3
};

class PowerUp : public Rectangle
{
protected:
	PowerUp(const glm::vec2& position, float duration, PowerUpType type);
public:
	~PowerUp() {};
public:
	void Update(float delta_time);
	void Move(float delta_time);
	void Activate(Ball& ball, Player& player);
	void Decativate(Ball& ball, Player& player);
public:
	float m_Duration;
	PowerUpType m_Type;
	PowerUpState m_State = PowerUpState::Falling;
	friend class PowerUpSystem;
};