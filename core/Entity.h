#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/System.hpp>
#include <SFML/Network.hpp>

struct EntityID
{
    sf::Uint32 h;
    sf::Uint32 l;
};

bool operator<(const EntityID &a, const EntityID &b);
sf::Packet &operator<<(sf::Packet &packet, const EntityID &id);
sf::Packet &operator>>(sf::Packet &packet, EntityID &id);
EntityID operator++(EntityID &id);

class Entity
{
    public:
        Entity();
        Entity(const EntityID &id, float mass, bool movable);
        virtual ~Entity();

        void AddAcceleration(const sf::Vector2f &dAcceleration);
        void MoveTo(const sf::Vector2f &position);
        void UpdatePhysics();

        EntityID GetID() const;

        sf::Vector2f GetVectorTo(const sf::Vector2f &target) const;
        sf::Vector2f GetNextVelocity() const;
        sf::Vector2f GetNextPosition() const;
        
        friend sf::Packet &operator<<(sf::Packet &packet, const Entity &entity);
        friend sf::Packet &operator>>(sf::Packet &packet, Entity &entity);

    protected:
        EntityID id; 
        float mass;
        bool movable;
        sf::Vector2f acceleration;
        sf::Vector2f velocity;
        sf::Vector2f position;

        static const float FRAME_DT;
};

#endif

