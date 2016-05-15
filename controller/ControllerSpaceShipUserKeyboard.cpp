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
    if(event.type == sf::Event::KeyPressed)
    {
        if(event.key.code == sf::Keyboard::Right)
            spaceship.ChangeDirection({1, 0});
        else if(event.key.code == sf::Keyboard::Left)
            spaceship.ChangeDirection({-1, 0});
        else if(event.key.code == sf::Keyboard::Up)
            spaceship.ChangeDirection({0, -1});
        else if(event.key.code == sf::Keyboard::Down)
            spaceship.ChangeDirection({0, 1});
        else if(event.key.code == sf::Keyboard::Space)
            spaceship.Thrust();
    }
}

