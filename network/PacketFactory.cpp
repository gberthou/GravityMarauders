#include <PacketFactory.h>

void PacketFactory::BuildConnectionReqPacket(sf::Packet &packet)
{
    packet << static_cast<sf::Uint8>(PT_CONNECTION_REQ);
}

void PacketFactory::BuildConnectionAckPacket(sf::Packet &packet)
{
    packet << static_cast<sf::Uint8>(PT_CONNECTION_ACK);
}

void PacketFactory::BuildMapReqPacket(sf::Packet &packet)
{
    packet << static_cast<sf::Uint8>(PT_MAP_REQ);
}

void PacketFactory::BuildMapAnsPacket(sf::Packet &packet, const Map &map)
{
    packet << static_cast<sf::Uint8>(PT_MAP_ANS) << map;
}

void PacketFactory::BuildFormationPushPacket(sf::Packet &packet,
                                             const Formation &formation)
{
    packet << static_cast<sf::Uint8>(PT_FORMATION_PUSH) << formation;
}

void PacketFactory::BuildFormationAckPacket(sf::Packet &packet)
{
    packet << static_cast<sf::Uint8>(PT_FORMATION_ACK);
}

void PacketFactory::BuildSpawnPushPacket(sf::Packet &packet)
{
    packet << static_cast<sf::Uint8>(PT_SPAWN_PUSH);
}

void PacketFactory::BuildSpawnAckPacket(sf::Packet &packet,
    const Snapshot &snapshot, const std::vector<Entity*> &entities)
{
    packet << static_cast<sf::Uint8>(PT_SPAWN_ACK)
           << snapshot
           << static_cast<sf::Uint32>(entities.size());
    for(Entity *entity : entities)
    {
        packet << entity->GetID();
    }
}

PacketType PacketFactory::GetPacketType(sf::Packet &packet)
{
    sf::Uint8 ptype;
    packet >> ptype;
    return static_cast<PacketType>(ptype);
}

