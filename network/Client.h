#ifndef CLIENT_H
#define CLIENT_H

#include <SFML/Network.hpp>

#include <Map.h>

enum ClientState
{
    CS_CREATED,
    CS_CONNECTED_NO_MAP,
    CS_INITIALIZED
};

class Client : protected sf::UdpSocket
{
    public:
        Client(const sf::IpAddress &serverAddress, Map &map);
        virtual ~Client();

        bool Connect();
        bool WaitForConnectionAck(const sf::Time &timeout);
        bool WaitForMap(const sf::Time &timeout);
        bool Receive();

    protected:
        void sendPacket(sf::Packet &packet);
        void onPacketReceived(sf::Packet &packet,
                              const sf::IpAddress &ipAddress,
                              unsigned short port);

        ClientState state;
        sf::IpAddress serverAddress;
        
        Map &map;
};

#endif

