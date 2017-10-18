#include <ViewTracks.h>
#include <ViewTrackSpaceShip.h>

const size_t LINE_POINTS = 256;
const float  FRAME_STEP  = 16.f;

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
            ViewTrackSpaceShip(LINE_POINTS, FRAME_STEP, *spaceship, map).draw(target, states);
        }
    }
}

