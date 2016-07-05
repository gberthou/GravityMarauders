#include <iostream>

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
    std::pair<EntityID, Entity*> pair(entity.GetID(), entity.Copy());
    if(!entities.insert(pair).second)
        throw GameException("Trying to add an entity with an ID that already "
                            "exists to a snapshot");
}

const std::map<EntityID, Entity*> &Snapshot::GetEntities() const
{
    return entities;
}

sf::Packet &operator<<(sf::Packet &packet, const Snapshot &snapshot)
{
    packet << static_cast<sf::Uint32>(snapshot.entities.size());
    
    for(auto it : snapshot.entities)
    {
        packet << (sf::Uint8)(it.second->GetType());
        it.second->WriteToPacket(packet);
        
        EntityID id = it.second->GetID();
        std::cout << '(' << id.h << ", " << id.l << ')' << std::endl;
    }
    return packet;
}

sf::Packet &operator>>(sf::Packet &packet, Snapshot &snapshot)
{
    sf::Uint32 size;
    packet >> size;

    snapshot.entities.clear();
    for(sf::Uint32 i = 0; i < size; ++i)
    {
        sf::Uint8 eType;
        packet >> eType;

        Entity *value = Entity::CreateEntity(static_cast<EntityType>(eType));

        value->ReadFromPacket(packet);
    
        EntityID id = value->GetID();
        std::cout << '(' << id.h << ", " << id.l << ')' << std::endl;

        if(!snapshot.entities.insert(
           std::pair<EntityID, Entity*>(value->GetID(), value)).second)
            throw GameException("Received snapshot with double keys");
    }

    return packet;
}

