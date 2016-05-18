#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/System.hpp>
#include <SFML/Network.hpp>

class Entity
{
    public:
        Entity(float mass, bool movable);
        virtual ~Entity();

        void AddAcceleration(const sf::Vector2f &dAcceleration);
        void MoveTo(const sf::Vector2f &position);
        void UpdatePhysics();

        sf::Vector2f GetVectorTo(const sf::Vector2f &target) const;
        sf::Vector2f GetNextVelocity() const;
        sf::Vector2f GetNextPosition() const;
        
        friend sf::Packet &operator<<(sf::Packet &packet, const Entity &entity);
        friend sf::Packet &operator>>(sf::Packet &packet, Entity &entity);

    protected:
        float mass;
        bool movable;
        sf::Vector2f acceleration;
        sf::Vector2f velocity;
        sf::Vector2f position;

        static const float FRAME_DT;
};

#endif

