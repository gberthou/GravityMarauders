#include <ViewSpaceShip.h>
#include <Resources.h>

ViewSpaceShip::ViewSpaceShip(const SpaceShip &sp):
    spaceship(sp)
{
}

ViewSpaceShip::~ViewSpaceShip()
{
}

void ViewSpaceShip::CenterWindowView(sf::RenderWindow &window) const
{
    sf::Vector2u windowSize = window.getSize();
    sf::View view(sf::FloatRect(0, 0, windowSize.x, windowSize.y));
    view.setCenter(spaceship.position);
    view.setRotation(spaceship.angle);
    window.setView(view);
}

void ViewSpaceShip::draw(sf::RenderTarget &target, sf::RenderStates states)
    const
{
    sf::Sprite sprite =
        Resources::CreateCenteredSprite(Resources::texSpaceships[0]);
    sprite.setPosition(spaceship.position);
    sprite.setRotation(spaceship.angle);

    target.draw(sprite, states);
}

