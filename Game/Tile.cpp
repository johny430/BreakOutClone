#include "Tile.h"

Tile::Tile(const glm::vec2& position, const glm::vec2& size, const glm::vec3& color, bool is_solid) :
    Rectangle(position,size), m_Color(color), m_Solid(is_solid)
{
}

bool Tile::IsActive() const
{
    return !m_Destroyed;
}

bool Tile::IsSolid() const
{
    return m_Solid;
}
