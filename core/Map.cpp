#include <Map.h>
#include <Utils.hpp>

Map::Map()
{
}

Map::~Map()
{
}

void Map::AddPlanet(Planet &planet)
{
    planets.push_back(planet);
    expandBounds(planet, planets.size() == 1);
}

sf::Vector2f Map::AccelerationAppliedAt(const sf::Vector2f &position) const
{
    sf::Vector2f ret(0.f, 0.f);
    for(Planet planet : planets)
        ret += planet.AccelerationAppliedAt(position);
    return ret;
}

void Map::ApplyGravityTo(Entity &entity) const
{
    for(Planet planet : planets)
        planet.ApplyGravityTo(entity);
}

sf::Packet &operator<<(sf::Packet &packet, const Map &map)
{
    packet << static_cast<sf::Uint32>(map.planets.size());
    for(Planet planet : map.planets)
        planet.WriteToPacket(packet);
    return packet;
}

sf::Packet &operator>>(sf::Packet &packet, Map &map)
{
    sf::Uint32 planetCount;
    packet >> planetCount;

    map.planets.resize(planetCount);
    for(sf::Uint32 i = 0; i < planetCount; ++i)
    {
        map.planets[i].ReadFromPacket(packet);
        map.expandBounds(map.planets[i], i == 0);
    }
    return packet;
}

void Map::expandBounds(const Planet &planet, bool firstPlanet)
{
    float radius = planet.GetRadius();
    sf::Vector2f corner =
        planet.GetPosition() - sf::Vector2f(radius, radius);

    if(firstPlanet)
    {
        bounds.left   = corner.x;
        bounds.top    = corner.y;
        bounds.width  = 2 * radius;
        bounds.height = 2 * radius;
    }
    else
    {
        sf::Vector2f oldMax(bounds.left + bounds.width, bounds.top + bounds.height);

        bounds.left   = min(bounds.left, corner.x);
        bounds.top    = min(bounds.top, corner.y);
        bounds.width  =
            max(oldMax.x, corner.x + 2 * radius) - bounds.left;
        bounds.height =
            max(oldMax.y, corner.y + 2 * radius) - bounds.top;
    }
}
