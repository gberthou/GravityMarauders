#ifndef FORMATION_H
#define FORMATION_H

#include <vector>

#include <SFML/System.hpp>

#include <SpaceShip.h>

struct FormationSlot
{
    int gridX;
    int gridY;

    SpaceShip &spaceship;
    
    bool IsLeader() const
    {
        return gridX == 0 && gridY == 0;
    }
};

class Formation
{
    public:
        Formation(const sf::Vector2f &gridUnit);
        virtual ~Formation();

        void AddSlot(int gridX, int gridY, SpaceShip &spaceship);

    protected:
        sf::Vector2f gridUnit;
        std::vector<FormationSlot> slots;
        const SpaceShip *leader;

        friend class ViewFormation;
        friend class ControllerFormation;
};

#endif

