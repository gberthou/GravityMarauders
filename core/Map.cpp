#include <Map.h>

Map::Map()
{
}

Map::~Map()
{
}

void Map::AddPlanet(Planet &planet)
{
    planets.push_back(planet);
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
        map.planets[i].ReadFromPacket(packet);
    return packet;
}

