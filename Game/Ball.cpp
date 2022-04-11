#include "Ball.h"

Ball::Ball(const glm::vec2& position, const glm::vec2& velocity, float radius) :
	Circle(position,radius), Velocity(velocity)
{
}

Ball::~Ball()
{
}

void Ball::Move(float delta_time)
{
	Position += Velocity * delta_time;
}

void Ball::Follow(Player& player)
{
	Position.x = player.Position.x;
	Position.y = player.Position.y + player.Size.y / 2.0f + Radius;
}
