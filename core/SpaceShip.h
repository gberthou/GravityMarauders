#ifndef SPACESHIP_H
#define SPACESHIP_H

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include <Entity.h>
#include <Planet.h>

extern const float MAX_THRUST;

class SpaceShip: public Entity
{
    public:
        SpaceShip();
        SpaceShip(const EntityID &i, float mass);
        SpaceShip(const SpaceShip &spaceship);
        virtual ~SpaceShip();

        void Rotate(float angleDegrees);

        // Tries to adjust direction so that it matches with the one given as
        // a parameter.
        // Returns the actual direction after rotation.
        // Contract: targetDirection must be normalized before calling
        //           this method
        sf::Vector2f ChangeDirection(const sf::Vector2f &targetDirection);
       
        void GoToPoint(const sf::Vector2f &destination,
                       const sf::Vector2f &targetVelocity);

        void Thrust(float thrustIntensity = MAX_THRUST * 2./3.);
        void StopThrust();
        void FollowOrbit(const Planet &planet);
        
        virtual sf::Packet &WriteToPacket(sf::Packet &packet) const;
        virtual sf::Packet &ReadFromPacket(sf::Packet &packet);
        
        virtual Entity *Copy() const;
        
    protected:
        float angle; // Degrees
        sf::Transform localMatrix;
        bool thrustEnabled;

        void generateForce(const sf::Vector2f &idealForce);

        friend class ViewSpaceShip;
        friend class ViewTrackSpaceShip;
        friend class ViewFormation;
        friend class ControllerSpaceShipUserKeyboard;
        friend class ControllerFormation;
};

#endif

