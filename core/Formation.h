#ifndef FORMATION_H
#define FORMATION_H

#include <vector>

#include <SFML/System.hpp>
#include <SFML/Network.hpp>

#include <SpaceShip.h>

struct FormationSlotDescriptor
{
    int gridX;
    int gridY;

    // TODO: Add spaceship type
};

struct FormationSlot
{
    FormationSlotDescriptor desc;

    SpaceShip &spaceship;
    
    bool IsLeader() const
    {
        return desc.gridX == 0 && desc.gridY == 0;
    }
};

class Formation
{
    public:
        Formation(const sf::Vector2f &gridUnit);
        virtual ~Formation();

        void AddSlotDescriptor(int gridX, int gridY);
        //void AddSlot(int gridX, int gridY, SpaceShip &spaceship);

        friend sf::Packet &operator<<(sf::Packet &packet,
                                      const Formation &formation);
        friend sf::Packet &operator>>(sf::Packet &packet, Formation &formation);

    protected:
        sf::Vector2f gridUnit;
        std::vector<FormationSlotDescriptor> slotDescriptors; 
        std::vector<FormationSlot> slots;
        
        const SpaceShip *leader;

        friend class ViewFormation;
        friend class ControllerFormation;
};

#endif

