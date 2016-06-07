#include <Snapshot.h>
#include <GameException.h>

Snapshot::Snapshot()
{
}

Snapshot::~Snapshot()
{
}

void Snapshot::AddEntity(const Entity &entity)
{
    std::pair<EntityID, Entity> pair(entity.GetID(), entity);
    if(!entities.insert(pair).second)
        throw GameException("Trying to add an entity with an ID that already "
                            "exists to a snapshot");
}

sf::Packet &operator<<(sf::Packet &packet, const Snapshot &snapshot)
{
    packet << static_cast<sf::Uint32>(snapshot.entities.size());
    
    for(auto it : snapshot.entities)
        packet << it.first << it.second;
    return packet;
}

sf::Packet &operator>>(sf::Packet &packet, Snapshot &snapshot)
{
    sf::Uint32 size;
    packet >> size;

    snapshot.entities.clear();
    for(sf::Uint32 i = 0; i < size; ++i)
    {
        EntityID key;
        Entity value;
        packet >> key >> value;

        if(!snapshot.entities.insert(std::pair<EntityID, Entity>(key, value))
            .second)
            throw GameException("Received snapshot with double keys");
    }

    return packet;
}

