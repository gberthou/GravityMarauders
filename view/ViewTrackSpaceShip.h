#ifndef VIEW_TRACK_SPACESHIP_H
#define VIEW_TRACK_SPACESHIP_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <SpaceShip.h>
#include <Map.h>

class ViewTrackSpaceShip: public sf::Drawable
{
    public:
        ViewTrackSpaceShip(size_t pointCount, float step, const SpaceShip &sp,
                           const Map &m);
        virtual ~ViewTrackSpaceShip();

        virtual void draw(sf::RenderTarget &target, sf::RenderStates states)
            const;

    protected:
        size_t linePoints;
        float frameStep;
        const SpaceShip &spaceship;
        const Map       &map;
        sf::Vertex *vertices;
};

#endif

