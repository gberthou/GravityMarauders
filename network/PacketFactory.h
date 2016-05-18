#ifndef PACKET_FACTORY_H
#define PACKET_FACTORY_H

#include <SFML/Network.hpp>

#include <Map.h>

enum PacketType
{
    PT_CONNECTION_REQ,
    PT_CONNECTION_ACK,

    PT_MAP_REQ,
    PT_MAP_ANS
};

class PacketFactory
{
    public:
        static void BuildConnectionReqPacket(sf::Packet &packet);
        static void BuildConnectionAckPacket(sf::Packet &packet);

        static void BuildMapReqPacket(sf::Packet &packet);
        static void BuildMapAnsPacket(sf::Packet &packet, const Map &map);

        static PacketType GetPacketType(sf::Packet &packet);
};

#endif

