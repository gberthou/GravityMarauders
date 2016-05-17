#include <iostream>

#include <Client.h>
#include <Server.h>
#include <PacketFactory.h>
#include <GameException.h>

Client::Client(const sf::IpAddress &sAddress):
    state(CS_CREATED),
    serverAddress(sAddress)
{
    setBlocking(false);
}

Client::~Client()
{
}

bool Client::Connect()
{
    if(state == CS_CREATED)
    {
        sf::Packet packet;
        PacketFactory::BuildConnectionReqPacket(packet);

        if(send(packet, serverAddress, Server::PORT) != sf::Socket::Done)
            throw GameException("Client::Connect cannot contact server");
        return true;
    }
    return false;
}

bool Client::WaitForConnectionAck(const sf::Time &timeout)
{
    sf::SocketSelector selector;
    selector.add(*this);
    if(selector.wait(timeout))
    {
        Receive();
        return state == CS_CONNECTED;
    }
    return false;
}

bool Client::Receive()
{
    sf::Packet packet;
    sf::IpAddress ipAddress;
    unsigned short port;
    sf::Socket::Status status = receive(packet, ipAddress, port);

    if(status == sf::Socket::Done) // A packet has been received
    {
        onPacketReceived(packet, ipAddress, port);
        return true;
    }
    if(status != sf::Socket::NotReady) // Error
    {
        throw GameException("Client::Receive has failed");
    }
    return false;
}

void Client::onPacketReceived(sf::Packet &packet,
                              const sf::IpAddress &ipAddress,
                              unsigned short port)
{
    (void) port;
    (void) ipAddress;


    //if(ipAddress == serverAddress)
    {
        PacketType ptype = PacketFactory::GetPacketType(packet);
        std::cout << ptype << std::endl;
        if(ptype == PT_CONNECTION_ACK)
        {
            state = CS_CONNECTED;

            std::cout << "Successfully connected to " << ipAddress << std::endl;
        }
    }
}

