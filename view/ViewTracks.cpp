#include <ViewTracks.h>
#include <ViewTrackSpaceShip.h>

ViewTracks::ViewTracks(const EntityManager &em, const Map &m):
    entityManager(em),
    map(m)
{
}

ViewTracks::~ViewTracks()
{
}

void ViewTracks::draw(sf::RenderTarget &target, sf::RenderStates states)
    const
{
    for(auto it : entityManager.entities)
    {
        if(it.second->GetType() == ET_SPACESHIP)
        {
            SpaceShip *spaceship = static_cast<SpaceShip*>(it.second);
            ViewTrackSpaceShip(*spaceship, map).draw(target, states);
        }
    }
}

