#ifndef MAP_H
#define MAP_H

#include <vector>

#include <Planet.h>

struct PlanetContainer
{
    Planet &planet;
};

class Map
{
    public:
        Map();
        virtual ~Map();

        void AddPlanet(Planet &planet);
        void ApplyGravityTo(Entity &entity) const;

    protected:
        std::vector<PlanetContainer> planets;

        friend class ViewMap;
};

#endif

