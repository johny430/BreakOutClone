#pragma once
#include "Engine/Physics/Colliders.h"

class Tile : public Rectangle
{
public:
	Tile(const glm::vec2& position, const glm::vec2& size, const glm::vec3& color, bool is_solid);
	~Tile() {};
	bool IsActive() const;
	bool IsSolid() const;
private:
	glm::vec3 m_Color;
	bool  m_Solid = false;
	float m_Destroyed = false;
	friend class GameLevel;
};