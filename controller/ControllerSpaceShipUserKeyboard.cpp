#include <ControllerSpaceShipUserKeyboard.h>

ControllerSpaceShipUserKeyboard::ControllerSpaceShipUserKeyboard(SpaceShip &sp):
    ControllerSpaceShipUser(sp)
{
}

ControllerSpaceShipUserKeyboard::~ControllerSpaceShipUserKeyboard()
{
}

void ControllerSpaceShipUserKeyboard::Update(const sf::Event &event)
{
    spaceship.StopThrust();
    if(event.type == sf::Event::KeyPressed)
    {
        if(event.key.code == sf::Keyboard::Right)
            spaceship.Rotate(45);
        else if(event.key.code == sf::Keyboard::Left)
            spaceship.Rotate(-45);
        else if(event.key.code == sf::Keyboard::Space)
            spaceship.Thrust();
    }
}

