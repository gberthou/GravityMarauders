#include <iostream>
#include <cmath>

#include <Planet.h>
#include <GameException.h>

const float FOUR_THIRD_PI  = 4.188790205;
const float GRAVITY_FACTOR = 1./1024.;
const float EPSILON2       = 1; 

static float len2(const sf::Vector2f &v)
{
    return v.x * v.x + v.y * v.y;
}

Planet::Planet()
{
}

Planet::Planet(const EntityID &i, float density, float r):
    Entity(i, ET_PLANET, FOUR_THIRD_PI * r * r * r * density, false),
    radius(r)
{
}

Planet::Planet(const Planet &planet):
    Entity(planet),
    radius(planet.radius)
{
}

Planet::~Planet()
{
}

void Planet::ApplyGravityTo(Entity &entity) const
{
    sf::Vector2f direction = entity.GetVectorTo(position);
    float directionLen2 = len2(direction);

    if(directionLen2 > EPSILON2)
    {
        // deltaAcceleration(entity) = Force / entity.mass
        // divide by sqrt(directionLen2) to normalize direction
        sf::Vector2f deltaAcceleration = direction * (GRAVITY_FACTOR * mass /
                (static_cast<float>(sqrt(directionLen2))*directionLen2)); 
        
        entity.AddAcceleration(deltaAcceleration);
    }
}

sf::Packet &Planet::WriteToPacket(sf::Packet &packet) const
{
    packet << radius;
    return Entity::WriteToPacket(packet);
}

sf::Packet &Planet::ReadFromPacket(sf::Packet &packet)
{
    packet >> radius;
    return Entity::ReadFromPacket(packet);
}

Entity *Planet::Copy() const
{
    Entity *ret = new Planet(*this);
    if(ret == nullptr)
        throw GameException("Cannot allocate Planet");
    return ret;
}

