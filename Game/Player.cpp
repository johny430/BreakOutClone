#include "Player.h"

Player::Player(const glm::vec2& position, const glm::vec2& size)
	: Rectangle(position, size)
{
}

void Player::Move(const glm::vec2& movement)
{
	Position += movement;
}

Player::~Player()
{
}
