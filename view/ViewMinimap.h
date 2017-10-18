#ifndef VIEW_MINIMAP_H
#define VIEW_MINIMAP_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <Map.h>
#include <Formation.h>

class ViewMinimap: public sf::Drawable
{
    public:
        ViewMinimap(unsigned int w, unsigned int h, const Map &m,
                    const Formation &f);
        virtual ~ViewMinimap();

        void ApplyView(sf::RenderWindow &window) const;

        virtual void draw(sf::RenderTarget &target, sf::RenderStates states)
            const;

    protected:
        unsigned int width;
        unsigned int height;
        const Map &map;
        const Formation &formation;
};


#endif

