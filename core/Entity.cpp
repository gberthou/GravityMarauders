#include <Entity.h>
#include <NetworkUtils.h>

const float Entity::FRAME_DT = 1.f / 120.f;
    
Entity::Entity(float m, bool mov):
    mass(m),
    movable(mov)
{
}

Entity::~Entity()
{
}

void Entity::AddAcceleration(const sf::Vector2f &dAcceleration)
{
    acceleration += dAcceleration;
}

void Entity::MoveTo(const sf::Vector2f &pos)
{
    position = pos;
}

void Entity::UpdatePhysics()
{
    if(movable)
    {
        velocity += acceleration * FRAME_DT;
        position += velocity * FRAME_DT;

        acceleration = {0, 0};
    }
}

sf::Vector2f Entity::GetVectorTo(const sf::Vector2f &target) const
{
    return target - position;
}

sf::Vector2f Entity::GetNextVelocity() const
{
    return velocity + acceleration * FRAME_DT;
}

sf::Vector2f Entity::GetNextPosition() const
{
    return position + GetNextVelocity() * FRAME_DT;
}

sf::Packet &operator<<(sf::Packet &packet, const Entity &entity)
{
    return packet << entity.mass << static_cast<sf::Uint8>(entity.movable)
                  << entity.acceleration << entity.velocity << entity.position;
}

sf::Packet &operator>>(sf::Packet &packet, Entity &entity)
{
    sf::Uint8 movable;
    packet >> entity.mass >> movable
           >> entity.acceleration >> entity.velocity >> entity.position;
    entity.movable = (movable != 0);

    return packet;
}

