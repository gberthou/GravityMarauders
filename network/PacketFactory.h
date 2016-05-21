#ifndef PACKET_FACTORY_H
#define PACKET_FACTORY_H

#include <SFML/Network.hpp>

#include <Map.h>
#include <Formation.h>

enum PacketType
{
    PT_CONNECTION_REQ,
    PT_CONNECTION_ACK,

    PT_MAP_REQ,
    PT_MAP_ANS,

    PT_FORMATION_PUSH,
    PT_FORMATION_ACK
};

class PacketFactory
{
    public:
        static void BuildConnectionReqPacket(sf::Packet &packet);
        static void BuildConnectionAckPacket(sf::Packet &packet);

        static void BuildMapReqPacket(sf::Packet &packet);
        static void BuildMapAnsPacket(sf::Packet &packet, const Map &map);

        static void BuildFormationPushPacket(sf::Packet &packet,
                                             const Formation &formation);
        static void BuildFormationAckPacket(sf::Packet &packet);

        static PacketType GetPacketType(sf::Packet &packet);
};

#endif

