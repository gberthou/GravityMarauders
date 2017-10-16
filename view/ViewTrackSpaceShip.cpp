#include <ViewTrackSpaceShip.h>
#include <Entity.h>

const size_t LINE_POINTS = 256;
const float  FRAME_STEP  = 16.f;

ViewTrackSpaceShip::ViewTrackSpaceShip(const SpaceShip &sp, const Map &m):
    spaceship(sp),
    map(m)
{
}

ViewTrackSpaceShip::~ViewTrackSpaceShip()
{
}

void ViewTrackSpaceShip::draw(sf::RenderTarget &target, sf::RenderStates states)
    const
{
    (void) states;

    sf::Vertex vertices[LINE_POINTS];

    sf::Vector2f tmpPosition = spaceship.position;
    sf::Vector2f tmpVelocity = spaceship.velocity;

    for(size_t i = 0; i < LINE_POINTS; ++i)
    {
        sf::Vector2f acceleration = map.AccelerationAppliedAt(tmpPosition);

        vertices[i] = tmpPosition;
        
        tmpPosition += tmpVelocity * (FRAME_STEP * Entity::FRAME_DT);
        tmpVelocity += acceleration * (FRAME_STEP * Entity::FRAME_DT);
    }

    target.draw(vertices, LINE_POINTS, sf::LineStrip);
}

