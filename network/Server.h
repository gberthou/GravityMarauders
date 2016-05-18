#ifndef SERVER_H
#define SERVER_H

#include <set>

#include <SFML/Network.hpp>

#include <Map.h>

struct ClientDesc
{
    sf::IpAddress ip;
    unsigned short port;
};

bool operator<(const ClientDesc & c1, const ClientDesc &c2);

class Server : protected sf::UdpSocket
{
    public:
        Server(const Map &map);
        virtual ~Server();

        bool Receive();

        static const unsigned short PORT = 41337;

    protected:
        void sendPacket(sf::Packet &packet, const sf::IpAddress &ipAddress,
                        unsigned short port);
        void onPacketReceived(sf::Packet &packet,
                              const sf::IpAddress &ipAddress,
                              unsigned short port);

        std::set<ClientDesc> clients;
        
        const Map &map;
};

#endif

