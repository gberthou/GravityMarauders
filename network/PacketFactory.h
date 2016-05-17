#ifndef PACKET_FACTORY_H
#define PACKET_FACTORY_H

#include <SFML/Network.hpp>

enum PacketType
{
    PT_CONNECTION_REQ,
    PT_CONNECTION_ACK
};

class PacketFactory
{
    public:
        static void BuildConnectionReqPacket(sf::Packet &packet);
        static void BuildConnectionAckPacket(sf::Packet &packet);

        static PacketType GetPacketType(sf::Packet &packet);
};

#endif

