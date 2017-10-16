#ifndef PLANET_H
#define PLANET_H

#include <SFML/Network.hpp>

#include <Entity.h>

class Planet: public Entity
{
    public:
        Planet();
        Planet(const EntityID &i, float density, float rad);
        Planet(const Planet &planet);
        virtual ~Planet();

        sf::Vector2f AccelerationAppliedAt(const sf::Vector2f &p) const;
        void ApplyGravityTo(Entity &entity) const;
        
        virtual sf::Packet &WriteToPacket(sf::Packet &packet) const;
        virtual sf::Packet &ReadFromPacket(sf::Packet &packet);
        
        virtual Entity *Copy() const;

    protected:
        float radius;

        friend class ViewPlanet;
};

#endif

