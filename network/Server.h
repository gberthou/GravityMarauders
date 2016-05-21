#ifndef SERVER_H
#define SERVER_H

#include <map>

#include <SFML/Network.hpp>

#include <Map.h>
#include <Formation.h>

struct ClientDesc
{
    sf::IpAddress ip;
    unsigned short port;
};

struct ClientContent
{
    Formation formation;
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

        std::map<ClientDesc, ClientContent> clients;
        
        const Map &map;
};

#endif

