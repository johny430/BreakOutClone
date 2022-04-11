#include "PowerUpSystem.h"

PowerUpSystem::PowerUpSystem(Ball& ball, Player& player) :
    m_CurrentBall(ball), m_CurrentPlayer (player)
{
    srand(time(0));
    ResourceLoader::Texture2DFromImage(m_SpeedTexture, "assets/texture/powerup_speed.png");
    ResourceLoader::Texture2DFromImage(m_StickyTexture,"assets/texture/powerup_sticky.png");
    ResourceLoader::Texture2DFromImage(m_IncreaseTexture,"assets/texture/powerup_increase.png");
    ResourceLoader::Texture2DFromImage(m_PassTexture,"assets/texture/powerup_passthrough.png");
}

PowerUpSystem::~PowerUpSystem()
{
}

void PowerUpSystem::Update(float delta_time)
{
    for (auto& power_up : m_PowerUps)
    {
        if (power_up.m_State == PowerUpState::Active)
        {
            power_up.Update(delta_time);
            if (power_up.m_Duration <= 0.0f)
            {
                power_up.Decativate(m_CurrentBall, m_CurrentPlayer);
            }
        }
        else if (power_up.m_State == PowerUpState::Falling) {
            power_up.Move(delta_time);
            if (power_up.Position.y <= 0.0f)
            {
                power_up.m_State = PowerUpState::Disabled;
            }
        }
    }
    m_PowerUps.erase(std::remove_if(this->m_PowerUps.begin(), this->m_PowerUps.end(),
        [](const PowerUp& powerUp) { 
            return powerUp.m_State == PowerUpState::Disabled;
        }
    ), this->m_PowerUps.end());
}

void PowerUpSystem::Spawn(const glm::vec2& position)
{
    constexpr int chance = 50;
    if (ShouldSpawn(chance)) {
        this->m_PowerUps.push_back(PowerUp(position, 5.0f,PowerUpType::Speed));
    }
    else if (ShouldSpawn(chance)) {
        this->m_PowerUps.push_back(PowerUp(position, 5.0f,PowerUpType::Sticky));
    }
    else if (ShouldSpawn(chance)) {
        this->m_PowerUps.push_back(PowerUp(position, 5.0f, PowerUpType::SizeUp));
    }
    else if (ShouldSpawn(chance)) {
        this->m_PowerUps.push_back(PowerUp(position, 5.0f,PowerUpType::PassThroug));
    }
}

void PowerUpSystem::CheckCollision()
{
    for (auto& power_up : m_PowerUps)
    {
        if (power_up.m_State == PowerUpState::Falling && Physics::CheckCollision(m_CurrentPlayer,power_up))
        {
            int index = 0;
            if (IsPowerUpActive(power_up.m_Type, index))
            {
                m_PowerUps[index].m_Duration += power_up.m_Duration;
                power_up.m_State = PowerUpState::Disabled;
            }
            else {
                power_up.Activate(m_CurrentBall, m_CurrentPlayer);
            }
        }
    }
}

bool PowerUpSystem::ShouldSpawn(unsigned int chance)
{
    unsigned int random = rand() % chance;
    return random == 0;
}

bool PowerUpSystem::IsPowerUpActive(PowerUpType type, int& index)
{
    for(unsigned int i = 0; i < m_PowerUps.size(); i++)
    {
        PowerUp& current = m_PowerUps[i];
        if (current.m_State == PowerUpState::Active && current.m_Type == type)
        {
            index = i;
            return true;
        }
    }
    return false;
}

void PowerUpSystem::Draw()
{
    for (auto& power_up : m_PowerUps)
    {
        if (power_up.m_State == PowerUpState::Falling)
        {
            switch (power_up.m_Type)
            {
            case PowerUpType::Speed:      Renderer::DrawSprite(m_SpeedTexture, power_up.Position, power_up.Size, glm::vec3(1.0f));
                break;
            case PowerUpType::Sticky:     Renderer::DrawSprite(m_StickyTexture, power_up.Position, power_up.Size, glm::vec3(1.0f));
                break;
            case PowerUpType::PassThroug: Renderer::DrawSprite(m_PassTexture, power_up.Position, power_up.Size, glm::vec3(1.0f));
                break;
            case PowerUpType::SizeUp:     Renderer::DrawSprite(m_IncreaseTexture, power_up.Position, power_up.Size, glm::vec3(1.0f));
                break;
            }
        }
    }
}

void PowerUpSystem::Reset()
{
    for (auto& power_up : m_PowerUps)
    {
        power_up.Decativate(m_CurrentBall,m_CurrentPlayer);
    }
    m_PowerUps.clear();
}
