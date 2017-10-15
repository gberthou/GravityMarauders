#ifndef VIEW_FORMATION_H
#define VIEW_FORMATION_H

#include <SFML/Graphics.hpp>

#include <Formation.h>

class ViewFormation: public sf::Drawable
{
    public:
        explicit ViewFormation(const Formation &f);
        virtual ~ViewFormation();

        virtual void draw(sf::RenderTarget &target, sf::RenderStates states)
            const;

        void CenterView(sf::RenderWindow &window);

    protected:
        const Formation &formation;
};

#endif

