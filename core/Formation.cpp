#include <Formation.h>
#include <NetworkUtils.h>
#include <GameException.h>

Formation::Formation(const sf::Vector2f &gu):
    gridUnit(gu),
    leader(nullptr)
{
}

Formation::~Formation()
{
}

void Formation::AddSlotDescriptor(int gridX, int gridY)
{
    FormationSlotDescriptor desc = {gridX, gridY};
    slotDescriptors.push_back(desc);
}

void Formation::Spawn(EntityManager &manager, std::vector<Entity*> &entities)
    const
{
    entities.clear();
    for(FormationSlotDescriptor slot : slotDescriptors)
    {
        // TODO: Add several spaceship types
        (void) slot;
        Entity *entity = manager.AddSpaceShip(200);
        entities.push_back(entity);
    }
}

void Formation::RefreshSpaceships(
        const std::vector<SpaceShip*> &spaceshipVector)
{
    if(slotDescriptors.size() != spaceshipVector.size())
    {
        throw GameException("Formation::RefreshSpaceships received wrong "
                            "parameter");
    }

    slots.clear();
    for(unsigned int i = 0; i < spaceshipVector.size(); ++i)
        slots.push_back({slotDescriptors[i], *spaceshipVector[i]});
    evaluateLeader();
}

sf::Packet &operator<<(sf::Packet &packet, const Formation &formation)
{
    packet << formation.gridUnit
           << static_cast<sf::Uint32>(formation.slotDescriptors.size());
    for(FormationSlotDescriptor slot : formation.slotDescriptors)
    {
        packet << slot.gridX << slot.gridY;
        // TODO
        // serialize spaceship descriptor
    }
    return packet;
}

sf::Packet &operator>>(sf::Packet &packet, Formation &formation)
{
    sf::Uint32 slotCount;

    packet >> formation.gridUnit >> slotCount;

    formation.slots.clear();
    formation.slotDescriptors.resize(slotCount);
    for(sf::Uint32 i = 0; i < slotCount; ++i)
    {
        packet >> formation.slotDescriptors[i].gridX
               >> formation.slotDescriptors[i].gridY;
    }
    
    return packet;
}

void Formation::evaluateLeader(void)
{
    const SpaceShip *ptr;
    unsigned int leaderCount = 0;
    for(auto it : slots)
    {
        if(it.IsLeader())
        {
            ptr = &it.spaceship;
            ++leaderCount;
        }
    }

    if(leaderCount != 1)
        throw GameException("Invalid formation");
    leader = ptr;
}

