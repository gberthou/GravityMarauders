#ifndef CONTROLLER_SPACESHIP_USER_KEYBOARD_H
#define CONTROLLER_SPACESHIP_USER_KEYBOARD_H

#include <ControllerSpaceShipUser.h>

class ControllerSpaceShipUserKeyboard: public ControllerSpaceShipUser
{
    public:
        ControllerSpaceShipUserKeyboard(SpaceShip &spaceship);
        virtual ~ControllerSpaceShipUserKeyboard();

        virtual void Update(const sf::Event &event);
};

#endif

