#include <iostream>

#include <ViewEntityManager.h>
#include <ViewSpaceShip.h>
#include <GameException.h>

ViewEntityManager::ViewEntityManager(const EntityManager &emanager):
    entityManager(emanager)
{
}

ViewEntityManager::~ViewEntityManager()
{
}

void ViewEntityManager::draw(sf::RenderTarget &target, sf::RenderStates states)
    const
{
    for(auto it : entityManager.entities)
    {
        switch(it.second->GetType())
        {
            case ET_PLANET:
                break;

            case ET_SPACESHIP:
                ViewSpaceShip(*static_cast<SpaceShip*>(it.second)).draw(target,
                                                                        states);
                break;

            default:
                throw GameException("Trying to display invalid entity");
        }
    }
}

