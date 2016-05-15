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
    for(auto it : map.planets)
    {
        ViewPlanet vPlanet(it.planet);
        target.draw(vPlanet, states);
    }
}

