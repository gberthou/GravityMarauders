#ifndef VIEW_TRACK_SPACESHIP_H
#define VIEW_TRACK_SPACESHIP_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <SpaceShip.h>
#include <Map.h>

class ViewTrackSpaceShip: public sf::Drawable
{
    public:
        explicit ViewTrackSpaceShip(const SpaceShip &sp, const Map &m);
        virtual ~ViewTrackSpaceShip();

        virtual void draw(sf::RenderTarget &target, sf::RenderStates states)
            const;

    protected:
        const SpaceShip &spaceship;
        const Map       &map;
};

#endif

