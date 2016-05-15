#ifndef VIEW_PLANET_H
#define VIEW_PLANET_H

#include <SFML/Graphics.hpp>

#include <Planet.h>

class ViewPlanet: public sf::Drawable
{
    public:
        ViewPlanet(const Planet &planet);
        virtual ~ViewPlanet();

        virtual void draw(sf::RenderTarget &target, sf::RenderStates states)
            const;

    protected:
        const Planet &planet;
};

#endif

