#ifndef VIEW_TRACKS_H
#define VIEW_TRACKS_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <EntityManager.h>
#include <Map.h>

class ViewTracks: public sf::Drawable
{
    public:
        explicit ViewTracks(const EntityManager &em, const Map &m);
        virtual ~ViewTracks();

        virtual void draw(sf::RenderTarget &target, sf::RenderStates states)
            const;

    protected:
        const EntityManager &entityManager;
        const Map           &map;
};

#endif

