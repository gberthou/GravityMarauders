#ifndef VIEW_SPACESHIP_H
#define VIEW_SPACESHIP_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <SpaceShip.h>

class ViewSpaceShip: public sf::Drawable
{
    public:
        explicit ViewSpaceShip(const SpaceShip &sp);
        virtual ~ViewSpaceShip();

        void CenterWindowView(sf::RenderWindow &window) const;

        virtual void draw(sf::RenderTarget &target, sf::RenderStates states)
            const;

    protected:
        const SpaceShip &spaceship;
};

#endif

