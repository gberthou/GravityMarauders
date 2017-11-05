#include <ViewEntityManager.h>
#include <ViewSpaceShip.h>
#include <GameException.h>

ViewEntityManager::ViewEntityManager(const EntityManager &em):
    entityManager(em)
{
}

ViewEntityManager::~ViewEntityManager()
{
}

void ViewEntityManager::draw(sf::RenderTarget &target, sf::RenderStates states)
    const
{
    for(const auto &it : entityManager.entities)
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

