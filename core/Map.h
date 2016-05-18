#ifndef MAP_H
#define MAP_H

#include <vector>

#include <SFML/Network.hpp>

#include <Planet.h>

class Map
{
    public:
        Map();
        virtual ~Map();

        void AddPlanet(Planet &planet);
        void ApplyGravityTo(Entity &entity) const;

        friend sf::Packet &operator<<(sf::Packet &packet, const Map &map);
        friend sf::Packet &operator>>(sf::Packet &packet, Map &map);

    protected:
        std::vector<Planet> planets;

        friend class ViewMap;
};

#endif

