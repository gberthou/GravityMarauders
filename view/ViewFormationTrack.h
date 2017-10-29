#ifndef VIEW_FORMATION_TRACK_H
#define VIEW_FORMATION_TRACK_H

#include <SFML/Graphics.hpp>

#include <Formation.h>
#include <Map.h>

class ViewFormationTrack: public sf::Drawable
{
    public:
        ViewFormationTrack(const Formation &f, const Map &m);
        virtual ~ViewFormationTrack();

        virtual void draw(sf::RenderTarget &target, sf::RenderStates states)
            const;

    protected:
        const Formation &formation;
        const Map &map;
};

#endif

