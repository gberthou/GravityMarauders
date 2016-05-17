#include <PacketFactory.h>

void PacketFactory::BuildConnectionReqPacket(sf::Packet &packet)
{
    packet << static_cast<sf::Uint8>(PT_CONNECTION_REQ);
}

void PacketFactory::BuildConnectionAckPacket(sf::Packet &packet)
{
    packet << static_cast<sf::Uint8>(PT_CONNECTION_ACK);
}

PacketType PacketFactory::GetPacketType(sf::Packet &packet)
{
    sf::Uint8 ptype;
    packet >> ptype;
    return static_cast<PacketType>(ptype);
}

