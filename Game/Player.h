#pragma once
#include <glm/glm.hpp>
#include "Engine/Engine.h"

class Player : public Rectangle
{
public:
	Player(const glm::vec2& position, const glm::vec2& size);
	void Move(const glm::vec2& movement);
	~Player();
};