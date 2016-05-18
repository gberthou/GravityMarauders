#ifndef PLANET_H
#define PLANET_H

#include <SFML/Network.hpp>

#include <Entity.h>

class Planet: public Entity
{
    public:
        Planet(float density = 1., float radius = 1.);
        virtual ~Planet();

        void ApplyGravityTo(Entity &entity) const;

        friend sf::Packet &operator<<(sf::Packet &packet, const Planet &planet);
        friend sf::Packet &operator>>(sf::Packet &packet, Planet &planet);

    protected:
        float radius;

        friend class ViewPlanet;
};

#endif

