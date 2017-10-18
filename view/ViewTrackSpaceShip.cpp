#include <ViewTrackSpaceShip.h>
#include <Entity.h>

ViewTrackSpaceShip::ViewTrackSpaceShip(size_t pointCount, float step,
                                       const SpaceShip &sp, const Map &m):
    linePoints(pointCount),
    frameStep(step),
    spaceship(sp),
    map(m)
{
    vertices = new sf::Vertex[linePoints];
}

ViewTrackSpaceShip::~ViewTrackSpaceShip()
{
    delete [] vertices;
}

void ViewTrackSpaceShip::draw(sf::RenderTarget &target, sf::RenderStates states)
    const
{
    (void) states;

    sf::Vector2f tmpPosition = spaceship.position;
    sf::Vector2f tmpVelocity = spaceship.velocity;

    for(size_t i = 0; i < linePoints; ++i)
    {
        sf::Vector2f acceleration = map.AccelerationAppliedAt(tmpPosition);

        vertices[i] = tmpPosition;
        
        tmpPosition += tmpVelocity * (frameStep * Entity::FRAME_DT);
        tmpVelocity += acceleration * (frameStep * Entity::FRAME_DT);
    }

    target.draw(vertices, linePoints, sf::LineStrip);
}

