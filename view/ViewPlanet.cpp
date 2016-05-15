#include <ViewPlanet.h>

ViewPlanet::ViewPlanet(const Planet &p):
    planet(p)
{
}

ViewPlanet::~ViewPlanet()
{
}

void ViewPlanet::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    sf::CircleShape circle;
    circle.setRadius(planet.radius);
    circle.setOutlineColor(sf::Color(0, 0, 255));
    circle.setOutlineThickness(4);
    circle.setFillColor(sf::Color(128, 128, 255));
    circle.setOrigin(sf::Vector2f(planet.radius, planet.radius));
    circle.setPosition(planet.position);
    circle.setPointCount(64);

    target.draw(circle, states);
}

