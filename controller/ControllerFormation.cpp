#include <cmath>

#include <ControllerFormation.h>
#include <ControllerSpaceShipUserKeyboard.h>
#include <GameException.h>

#include <Utils.hpp>

const float EPSILON2     = 0.01f; // EPSILON = 0.1
const float MAX_VELOCITY = 2.f;

ControllerFormation::ControllerFormation(Formation &f):
    formation(f)
{
}

ControllerFormation::~ControllerFormation()
{
}

void ControllerFormation::Update()
{
    if(!formation.IsValid())
        throw GameException("Invalid formation");

    for(auto it : formation.slots)
    {
        if(!it.IsLeader())
        {
            sf::Vector2f targetLocal =
                formation.leader->localMatrix.transformPoint(
                        {formation.gridUnit.x * it.desc.gridX,
                         formation.gridUnit.y * it.desc.gridY}
                );

            sf::Vector2f targetWorld =
                formation.leader->GetNextPosition() + targetLocal;
            
            it.spaceship.GoToPoint(targetWorld, formation.leader->velocity);
        }
    }
}

void ControllerFormation::Update(const sf::Event &event)
{
    if(formation.IsValid())
        ControllerSpaceShipUserKeyboard(*formation.leader).Update(event);
}

