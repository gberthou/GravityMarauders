#include <ViewMinimap.h>
#include <ViewMap.h>
#include <ViewTrackSpaceShip.h>

const size_t LINE_POINTS = 2048;
const float FRAME_STEP = 512.f;

ViewMinimap::ViewMinimap(unsigned int w, unsigned int h,
                         const Map &m, const Formation &f):
    width(w),
    height(h),
    map(m),
    formation(f)
{
}

ViewMinimap::~ViewMinimap()
{
}

void ViewMinimap::ApplyView(sf::RenderWindow &window) const
{
    sf::Vector2u windowSize = window.getSize();

    // World coordinates
    // TODO: Auto compute these values
    sf::View view(sf::FloatRect(-3600, -6600, 12800, 12800));

    // Top left corner (coordinates in range 0..1)
    view.setViewport(sf::FloatRect(0, 0, width / (float) windowSize.x,
                                         height / (float) windowSize.y));
    window.setView(view);
}

void ViewMinimap::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    sf::RectangleShape canvas(sf::Vector2f(12800, 12800));
    canvas.setFillColor(sf::Color(0, 0, 255, 128));
    canvas.setPosition(sf::Vector2f(-3600, -6600));
    // Draw minimap background
    target.draw(canvas, states);

    // Draw planets
    target.draw(ViewMap(map), states);

    // Draw predicted track of the player's spaceship
    // TODO: Draw only leader's track
    for(auto it : formation.slots)
    {
        ViewTrackSpaceShip(LINE_POINTS, FRAME_STEP, it.spaceship, map).draw(target, states);
    }
}

