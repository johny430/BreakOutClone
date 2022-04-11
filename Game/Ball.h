#pragma once
#include "Engine/Engine.h"
#include "Player.h"

class Ball : public Circle
{
public:
	Ball(const glm::vec2& position,const glm::vec2& velocity, float radius);
	~Ball();
	void Move(float delta_time);
	void Follow(Player& player);
public:
	glm::vec2 Velocity;
	bool Sticky = false;
	bool PassThrought = false;
};