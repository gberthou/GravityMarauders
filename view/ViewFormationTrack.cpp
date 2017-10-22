#include <ViewFormationTrack.h>
#include <ViewTrackSpaceShip.h>

const size_t LINE_POINTS = 256;
const float  FRAME_STEP  = 16.f;

ViewFormationTrack::ViewFormationTrack(const Formation &f, const Map &m):
    formation(f),
    map(m)
{
}

ViewFormationTrack::~ViewFormationTrack()
{
}

void ViewFormationTrack::draw(sf::RenderTarget &target, sf::RenderStates states)
    const
{
    ViewTrackSpaceShip(LINE_POINTS, FRAME_STEP, *formation.leader, map).draw(target, states);
}

