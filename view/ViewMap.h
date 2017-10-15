#ifndef VIEW_MAP_H
#define VIEW_MAP_H

#include <SFML/Graphics.hpp>

#include <Map.h>

class ViewMap: public sf::Drawable
{
    public:
        explicit ViewMap(const Map &m);
        virtual ~ViewMap();

        virtual void draw(sf::RenderTarget &target, sf::RenderStates states)
            const;

    protected:
        const Map &map;
};

#endif

