#ifndef MAP_H
#define MAP_H

#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

#include <Planet.h>

class Map
{
    public:
        Map();
        virtual ~Map();

        void AddPlanet(Planet &planet);
        sf::Vector2f AccelerationAppliedAt(const sf::Vector2f &position) const;
        void ApplyGravityTo(Entity &entity) const;

        const Planet &ClosestPlanetTo(const sf::Vector2f &position) const;

        friend sf::Packet &operator<<(sf::Packet &packet, const Map &map);
        friend sf::Packet &operator>>(sf::Packet &packet, Map &map);

    protected:
        std::vector<Planet> planets;
        sf::FloatRect bounds;

        void expandBounds(const Planet &planet, bool firstPlanet);

        friend class ViewMap;
        friend class ViewMinimap;
};

#endif

