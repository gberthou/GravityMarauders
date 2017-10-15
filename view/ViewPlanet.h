#ifndef VIEW_PLANET_H
#define VIEW_PLANET_H

#include <SFML/Graphics.hpp>

#include <Planet.h>

class ViewPlanet: public sf::Drawable
{
    public:
        explicit ViewPlanet(const Planet &p);
        virtual ~ViewPlanet();

        virtual void draw(sf::RenderTarget &target, sf::RenderStates states)
            const;

    protected:
        const Planet &planet;
};

#endif

