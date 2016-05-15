#include <Formation.h>

Formation::Formation(const sf::Vector2f &gu):
    gridUnit(gu),
    leader(nullptr)
{
}

Formation::~Formation()
{
}

void Formation::AddSlot(int gridX, int gridY, SpaceShip &spaceship)
{
    FormationSlot slot = {gridX, gridY, spaceship};
    if(slot.IsLeader())
        leader = &spaceship;
    slots.push_back(slot);
}

