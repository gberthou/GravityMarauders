#include <iostream>
#include <cmath>

#include <Planet.h>

const float FOUR_THIRD_PI  = 4.188790205;
const float GRAVITY_FACTOR = 1./1024.;
const float EPSILON2       = 1; 

static float len2(const sf::Vector2f &v)
{
    return v.x * v.x + v.y * v.y;
}

Planet::Planet(const EntityID &i, float density, float r):
    Entity(i, FOUR_THIRD_PI * r * r * r * density, false),
    radius(r)
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

sf::Packet &operator<<(sf::Packet &packet, const Planet &planet)
{
    return packet << planet.radius << static_cast<const Entity&>(planet);
}

sf::Packet &operator>>(sf::Packet &packet, Planet &planet)
{
    return packet >> planet.radius >> static_cast<Entity&>(planet);
}

