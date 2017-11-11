#include <ViewEntityManager.h>
#include <ViewSpaceShip.h>
#include <GameException.h>

ViewEntityManager::ViewEntityManager(const EntityManager &em):
    entityManager(em)
{
    // TODO: Add event system so that spaceship views are automatically
    // updated upon spaceship spawn or deletion

    for(const auto &it : entityManager.entities)
        if(it.second->GetType() == ET_SPACESHIP)
        {
            spViews.emplace_back(*static_cast<SpaceShip*>(it.second));
        }
}

ViewEntityManager::~ViewEntityManager()
{
}

void ViewEntityManager::draw(sf::RenderTarget &target, sf::RenderStates states)
    const
{
    for(const auto &view : spViews)
        target.draw(view, states);

    for(const auto &it : entityManager.entities)
    {
        switch(it.second->GetType())
        {
            case ET_PLANET:
            case ET_SPACESHIP:
                break;

            default:
                throw GameException("Trying to display invalid entity");
        }
    }
}

void ViewEntityManager::Update()
{
    for(auto &view : spViews)
        view.Update();
}
