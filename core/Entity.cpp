#include <Entity.h>
#include <NetworkUtils.h>

const float Entity::FRAME_DT = 1.f / 120.f;

bool operator<(const EntityID &a, const EntityID &b)
{
    if(a.h < b.h)
        return true;
    return a.l < b.l;
}

sf::Packet &operator<<(sf::Packet &packet, const EntityID &id)
{
    return packet << id.h << id.l;
}

sf::Packet &operator>>(sf::Packet &packet, EntityID &id)
{
    return packet >> id.h >> id.l;
}

EntityID operator++(EntityID &id)
{
    if(id.l + 1 == 0) // low overflow
        ++id.h;
    ++id.l;
    return id;
}

Entity::Entity()
{
}
    
Entity::Entity(const EntityID &i, float m, bool mov):
    id(i),
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

EntityID Entity::GetID() const
{
    return id;
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
    return packet << entity.id << entity.mass
                  << static_cast<sf::Uint8>(entity.movable)
                  << entity.acceleration << entity.velocity << entity.position;
}

sf::Packet &operator>>(sf::Packet &packet, Entity &entity)
{
    sf::Uint8 movable;
    packet >> entity.id >> entity.mass >> movable
           >> entity.acceleration >> entity.velocity >> entity.position;
    entity.movable = (movable != 0);

    return packet;
}

