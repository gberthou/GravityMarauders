#ifndef CONTROLLER_SPACESHIP_USER_H
#define CONTROLLER_SPACESHIP_USER_H

#include <SFML/Window.hpp>

#include <SpaceShip.h>

class ControllerSpaceShipUser
{
    public:
        explicit ControllerSpaceShipUser(SpaceShip &sp);
        virtual ~ControllerSpaceShipUser();

        virtual void Update(const sf::Event &event) = 0;

    protected:
        SpaceShip &spaceship;
};

#endif

