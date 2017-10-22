#ifndef FORMATION_H
#define FORMATION_H

#include <vector>
#include <functional>

#include <SFML/System.hpp>
#include <SFML/Network.hpp>

#include <SpaceShip.h>
#include <EntityManager.h>

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
        explicit Formation(const sf::Vector2f &gu);
        virtual ~Formation();

        void AddSlotDescriptor(int gridX, int gridY);
        void Spawn(EntityManager &manager, std::vector<Entity*> &entities)
            const;

        void RefreshSpaceships(const std::vector<SpaceShip*> &spaceshipVector);

        bool IsValid() const;

        friend sf::Packet &operator<<(sf::Packet &packet,
                                      const Formation &formation);
        friend sf::Packet &operator>>(sf::Packet &packet, Formation &formation);

    protected:
        void evaluateLeader(void);

        sf::Vector2f gridUnit;
        std::vector<FormationSlotDescriptor> slotDescriptors; 
        std::vector<FormationSlot> slots;
        
        SpaceShip *leader;

        friend class ViewFormation;
        friend class ViewFormationTrack;
        friend class ViewMinimap;
        friend class ControllerFormation;
        friend class ControllerFormationOrbit;
};

#endif

