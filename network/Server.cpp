#include <iostream>
#include <sstream>

#include <Server.h>
#include <PacketFactory.h>
#include <GameException.h>

bool operator<(const ClientDesc & c1, const ClientDesc &c2)
{
    if(c1.port < c2.port)
        return true;
    return c1.ip < c2.ip;
}

Server::Server()
{
    if(bind(PORT) != sf::Socket::Done)
    {
        std::ostringstream oss;
        oss << "Cannot open server on port " << Server::PORT;
        throw GameException(oss.str());
    }

    setBlocking(false);
}

Server::~Server()
{
    unbind();
}

bool Server::Receive()
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
        throw GameException("Server::Receive has failed");
    }
    return false;
}

void Server::onPacketReceived(sf::Packet &packet,
                              const sf::IpAddress &ipAddress,
                              unsigned short port)
{
    PacketType ptype = PacketFactory::GetPacketType(packet);
    if(ptype == PT_CONNECTION_REQ)
    {
        // Add client to the list of clients
        if(clients.insert({ipAddress, port}).second) // New client
        {
            std::cout << '[' << ipAddress << ':' << port
                      << "] is now connected!" << std::endl;
        }

        // Send connection ack packet
        sf::Packet response;
        PacketFactory::BuildConnectionAckPacket(response);
        if(send(response, ipAddress, port) != sf::Socket::Done)
            throw GameException("Cannot send CONNECTION_ACK to client");
    }
}

