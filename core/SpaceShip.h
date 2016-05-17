#ifndef SPACESHIP_H
#define SPACESHIP_H

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include <Entity.h>

extern const float MAX_THRUST;

class SpaceShip: public Entity
{
    public:
        SpaceShip(float mass);
        virtual ~SpaceShip();

        // Tries to adjust direction so that it matches with the one given as
        // a parameter.
        // Returns the actual direction after rotation.
        // Contract: targetDirection must be normalized before calling
        //           this method
        sf::Vector2f ChangeDirection(const sf::Vector2f &targetDirection);
       
        void GoToPoint(const sf::Vector2f &destination,
                       const sf::Vector2f &targetVelocity);

        void Thrust(float thrustIntensity = MAX_THRUST * 2./3.);

    protected:
        float angle; // Degrees
        sf::Transform localMatrix;

        friend class ViewSpaceShip;
        friend class ViewFormation;
        friend class ControllerSpaceShipUserKeyboard;
        friend class ControllerFormation;
};

#endif

