#ifndef RESOURCES_H
#define RESOURCES_H

#include <SFML/Graphics.hpp>

namespace Resources
{
    const unsigned int SPACESHIP_COUNT = 1;
    extern sf::Texture texSpaceships[SPACESHIP_COUNT];

    void LoadTextures();
    sf::Sprite CreateCenteredSprite(const sf::Texture &texture);
}

#endif

