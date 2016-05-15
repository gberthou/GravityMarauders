#include <Map.h>

Map::Map()
{
}

Map::~Map()
{
}

void Map::AddPlanet(Planet &planet)
{
    planets.push_back({planet});
}

void Map::ApplyGravityTo(Entity &entity) const
{
    for(auto it : planets)
    {
        it.planet.ApplyGravityTo(entity);
    }
}

