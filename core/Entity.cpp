#include <iostream>

#include <Entity.h>
#include <Planet.h>
#include <SpaceShip.h>
#include <NetworkUtils.h>
#include <GameException.h>

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
    
Entity::Entity(const EntityID &i, EntityType type, float m, bool mov):
    id(i),
    entityType(type),
    mass(m),
    movable(mov)
{
}

Entity::Entity(const Entity &entity):
    id(entity.id),
    entityType(entity.entityType),
    mass(entity.mass),
    movable(entity.movable),
    acceleration(entity.acceleration),
    velocity(entity.velocity),
    position(entity.position)
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

EntityType Entity::GetType() const
{
    return entityType;
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

sf::Packet &Entity::WriteToPacket(sf::Packet &packet) const
{
    return packet << id << mass
                  << static_cast<sf::Uint8>(entityType)
                  << static_cast<sf::Uint8>(movable)
                  << acceleration << velocity << position;
}

sf::Packet &Entity::ReadFromPacket(sf::Packet &packet)
{
    sf::Uint8 type;
    sf::Uint8 movable;
    packet >> id >> mass >> type >> movable
           >> acceleration >> velocity >> position;

    entityType = static_cast<EntityType>(type);
    movable = (movable != 0);

    return packet;
}

Entity *Entity::Copy() const
{
    Entity *ret = new Entity(*this);
    if(ret == nullptr)
        throw GameException("Cannot allocate Entity");
    return ret;
}

Entity *Entity::CreateEntity(EntityType entityType)
{
    Entity *ret = nullptr;
    switch(entityType)
    {
        case ET_PLANET:
            ret = new Planet;
            break;

        case ET_SPACESHIP:
            ret = new SpaceShip;
            break;

        default:
            throw GameException("Trying to create entity with wrong type");
            break;
    }

    if(ret == nullptr)
        throw GameException("Cannot allocate entity");
    return ret;
}

