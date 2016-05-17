#ifndef SERVER_H
#define SERVER_H

#include <set>

#include <SFML/Network.hpp>

struct ClientDesc
{
    sf::IpAddress ip;
    unsigned short port;
};

bool operator<(const ClientDesc & c1, const ClientDesc &c2);

class Server : protected sf::UdpSocket
{
    public:
        Server();
        virtual ~Server();

        bool Receive();

        static const unsigned short PORT = 41337;

    protected:
        void onPacketReceived(sf::Packet &packet,
                              const sf::IpAddress &ipAddress,
                              unsigned short port);

        std::set<ClientDesc> clients;
};

#endif

