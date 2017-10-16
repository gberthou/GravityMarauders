#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/System.hpp>
#include <SFML/Network.hpp>

struct EntityID
{
    sf::Uint32 h;
    sf::Uint32 l;
};

enum EntityType
{
    ET_NONE,
    ET_PLANET,
    ET_SPACESHIP
};

bool operator<(const EntityID &a, const EntityID &b);
sf::Packet &operator<<(sf::Packet &packet, const EntityID &id);
sf::Packet &operator>>(sf::Packet &packet, EntityID &id);
EntityID operator++(EntityID &id);

class Entity
{
    public:
        Entity();
        Entity(const EntityID &i, EntityType type, float m,
               bool mov);
        Entity(const Entity &entity);
        virtual ~Entity();

        void AddAcceleration(const sf::Vector2f &dAcceleration);
        void MoveTo(const sf::Vector2f &pos);
        void UpdatePhysics();

        EntityID GetID() const;
        EntityType GetType() const;

        sf::Vector2f GetVectorTo(const sf::Vector2f &target) const;
        sf::Vector2f GetNextVelocity() const;
        sf::Vector2f GetPosition() const;
        sf::Vector2f GetNextPosition() const;
        
        virtual sf::Packet &WriteToPacket(sf::Packet &packet) const;
        virtual sf::Packet &ReadFromPacket(sf::Packet &packet);

        virtual Entity *Copy() const;

        static Entity *CreateEntity(EntityType entityType);

    protected:
        EntityID id;
        EntityType entityType; 
        float mass;
        bool movable;
        sf::Vector2f builtAcceleration;
        sf::Vector2f acceleration;
        sf::Vector2f velocity;
        sf::Vector2f formerVelocity;
        sf::Vector2f position;

        static const float FRAME_DT;
};

#endif

