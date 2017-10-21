#ifndef CONTROLLER_FORMATION_ORBIT_H
#define CONTROLLER_FORMATION_ORBIT_H

#include <Formation.h>
#include <Map.h>
#include <Planet.h>

#include <SFML/Window.hpp>

class ControllerFormationOrbit
{
    public:
        ControllerFormationOrbit(Formation &f, const Map &m);
        virtual ~ControllerFormationOrbit();

        void Update();
        void Update(const sf::Event &event);

    protected:
        Formation &formation;
        const Map &map;
        bool enabled;
        const Planet *targetPlanet;
};

#endif

