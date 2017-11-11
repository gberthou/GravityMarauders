#ifndef VIEW_SPACESHIP_H
#define VIEW_SPACESHIP_H

#include <forward_list>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <SpaceShip.h>
#include <ParticleSystem.h>

class ViewSpaceShip: public sf::Drawable
{
    public:
        explicit ViewSpaceShip(const SpaceShip &sp);
        virtual ~ViewSpaceShip();

        void CenterWindowView(sf::RenderWindow &window) const;
        void Update();

        virtual void draw(sf::RenderTarget &target, sf::RenderStates states)
            const;

    protected:
        const SpaceShip &spaceship;
        std::forward_list<ParticleSystem> particleSystems;
        bool thrustEnabled;
};

#endif

