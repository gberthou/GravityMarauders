#ifndef CLIENT_H
#define CLIENT_H

#include <SFML/Network.hpp>

enum ClientState
{
    CS_CREATED,
    CS_CONNECTED
};

class Client : protected sf::UdpSocket
{
    public:
        Client(const sf::IpAddress &serverAddress);
        virtual ~Client();

        bool Connect();
        bool WaitForConnectionAck(const sf::Time &timeout);
        bool Receive();

    protected:
        void onPacketReceived(sf::Packet &packet,
                              const sf::IpAddress &ipAddress,
                              unsigned short port);

        ClientState state;
        sf::IpAddress serverAddress;
};

#endif

