#ifndef VIEW_ENTITY_MANAGER_H
#define VIEW_ENTITY_MANAGER_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <EntityManager.h>

class ViewEntityManager: public sf::Drawable
{
    public:
        explicit ViewEntityManager(const EntityManager &em);
        virtual ~ViewEntityManager();

        virtual void draw(sf::RenderTarget &target, sf::RenderStates states)
            const;

    protected:
        const EntityManager &entityManager;
};

#endif

