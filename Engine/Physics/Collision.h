#pragma once
#include <glm/glm.hpp>
#include "Colliders.h"  

enum class HitDirection {
    Verical,
    Horizontal,
    Corner
};

struct HitData
{
    HitDirection Direction;
};

class Physics
{
public:
    static bool CheckCollision(Circle& one, const Rectangle& two, HitData& data)
    {
        glm::vec2 aabb_half_extents(two.Size.x / 2.0f, two.Size.y / 2.0f);
        glm::vec2 difference = one.Position - two.Position;
        glm::vec2 closest = two.Position + glm::clamp(difference, -aabb_half_extents, aabb_half_extents);
        difference = closest - one.Position;
        if (glm::dot(difference,difference) <= one.Radius * one.Radius) {
            glm::vec2 return_vector;
            if (difference == glm::vec2(0.0f))
            {
                difference = one.Position - two.Position;
                constexpr float max_Size = 7680;
                difference.x *= max_Size;
                closest = two.Position + glm::clamp(difference, -aabb_half_extents, aabb_half_extents);
                difference = closest - one.Position;
                return_vector = -difference - glm::normalize(difference)  * one.Radius;
            }
            else {
                return_vector = glm::normalize(difference) * one.Radius - difference;
            }
            data.Direction = GetHitDirection(return_vector);
            one.Position -= return_vector;
            return true;
        }
        else {
            return false;
        }
    }

    static bool CheckCollision(const Rectangle& one, const Rectangle& two)
    {
        bool collisionX = one.Position.x + one.Size.x >= two.Position.x &&
            two.Position.x + two.Size.x >= one.Position.x;
        bool collisionY = one.Position.y + one.Size.y >= two.Position.y &&
            two.Position.y + two.Size.y >= one.Position.y;
        return collisionX && collisionY;
    }
private:
    static HitDirection GetHitDirection(glm::vec2 target)
    {
        if (target.x == 0.0f)
        {
            return HitDirection::Verical;
        }
        else if (target.y == 0.0f) {
            return HitDirection::Horizontal;
        } else{
            return HitDirection::Corner;
        }
    }
};