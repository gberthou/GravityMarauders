#include <ViewMap.h>
#include <ViewPlanet.h>

ViewMap::ViewMap(const Map &m):
    map(m)
{
}

ViewMap::~ViewMap()
{
}

void ViewMap::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    for(Planet planet : map.planets)
    {
        ViewPlanet vPlanet(planet);
        target.draw(vPlanet, states);
    }
}

