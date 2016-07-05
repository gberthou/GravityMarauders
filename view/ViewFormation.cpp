#include <ViewFormation.h>
#include <ViewSpaceShip.h>

ViewFormation::ViewFormation(const Formation &f):
    formation(f)
{
}

ViewFormation::~ViewFormation()
{
}

void ViewFormation::draw(sf::RenderTarget &target, sf::RenderStates states)
    const
{
    (void) target;
    (void) states;

    /*
    for(auto it : formation.slots)
    {
        ViewSpaceShip vSpaceship(it.spaceship);
        target.draw(vSpaceship, states);
    }

    // Debug purpose only
    for(auto it : formation.slots)
    {
        sf::Vector2f p = formation.leader->localMatrix.transformPoint(
            {formation.gridUnit.x * it.desc.gridX,
             formation.gridUnit.y * it.desc.gridY}
        );
        sf::CircleShape circle(10);
        circle.setFillColor(sf::Color(255, 255, 255));
        circle.setOrigin(5, 5);
        circle.setPosition(p + formation.leader->GetNextPosition());
        target.draw(circle, states);
    }
    */
}

void ViewFormation::CenterView(sf::RenderWindow &window)
{
    if(formation.leader != nullptr)
        ViewSpaceShip(*formation.leader).CenterWindowView(window);
}

