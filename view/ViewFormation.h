#ifndef VIEW_FORMATION_H
#define VIEW_FORMATION_H

#include <SFML/Graphics.hpp>

#include <Formation.h>

class ViewFormation: public sf::Drawable
{
    public:
        ViewFormation(const Formation &formation);
        virtual ~ViewFormation();

        virtual void draw(sf::RenderTarget &target, sf::RenderStates states)
            const;

    protected:
        const Formation &formation;
};

#endif

