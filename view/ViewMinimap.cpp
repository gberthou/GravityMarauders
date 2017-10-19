#include <ViewMinimap.h>
#include <ViewMap.h>
#include <ViewTrackSpaceShip.h>

const size_t LINE_POINTS = 2048;
const float FRAME_STEP = 512.f;

static sf::FloatRect squarify(const sf::FloatRect &rect)
{
    const float MARGIN = 1000.f;

    sf::FloatRect r = rect;
    r.left   -= MARGIN;
    r.top    -= MARGIN;
    r.width  += 2 * MARGIN;
    r.height += 2 * MARGIN;

    if(r.width == r.height)
        return r;
    if(r.width > r.height)
    {
        float delta = r.width - r.height;
        r.height = r.width;
        r.top -= delta / 2.f;
    }
    else // r.width < r.height
    {
        float delta = r.height - r.width;
        r.width = r.height;
        r.left -= delta / 2.f;
    }
    return r;
}

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
    sf::View view(squarify(map.bounds));

    // Top left corner (coordinates in range 0..1)
    view.setViewport(sf::FloatRect(0, 0, width / (float) windowSize.x,
                                         height / (float) windowSize.y));
    window.setView(view);
}

void ViewMinimap::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    sf::FloatRect bounds = squarify(map.bounds);
    sf::RectangleShape canvas(sf::Vector2f(bounds.width, bounds.height));
    canvas.setFillColor(sf::Color(0, 0, 255, 128));
    canvas.setPosition(sf::Vector2f(bounds.left, bounds.top));

    // Draw minimap background
    target.draw(canvas, states);

    // Draw planets
    target.draw(ViewMap(map), states);

    // Draw predicted track of the leader's spaceship
    ViewTrackSpaceShip(LINE_POINTS, FRAME_STEP, *formation.leader, map).draw(target, states);
}

