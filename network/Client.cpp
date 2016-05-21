#include <iostream>

#include <Client.h>
#include <Server.h>
#include <PacketFactory.h>
#include <GameException.h>

Client::Client(const sf::IpAddress &sAddress, Map &m, Formation &f):
    state(CS_CREATED),
    serverAddress(sAddress),
    map(m),
    formation(f)
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
        sendPacket(packet);
        return true;
    }
    return false;
}

bool Client::WaitForConnectionAck(const sf::Time &timeout)
{
    if(state == CS_CREATED)
    {
        sf::SocketSelector selector;
        selector.add(*this);
        if(selector.wait(timeout))
        {
            Receive();
            if(state == CS_CONNECTED_NO_MAP) // Connection accepted
            {
                sf::Packet packet;
                PacketFactory::BuildMapReqPacket(packet);
                sendPacket(packet);
                return true;
            }
        }
    }
    return false;
}

bool Client::WaitForMap(const sf::Time &timeout)
{
    if(state == CS_CONNECTED_NO_MAP)
    {
        sf::SocketSelector selector;
        selector.add(*this);
        if(selector.wait(timeout))
        {
            Receive();
            if(state == CS_MAPOK_SEND_INFOS) // Map received
                return true;
        }
    }
    return false;
}

bool Client::WaitForInfoTransferred(const sf::Time &timeout)
{
    if(state == CS_MAPOK_SEND_INFOS)
    {
        sf::SocketSelector selector;
        selector.add(*this);
        if(selector.wait(timeout))
        {
            Receive();
            if(state == CS_INITIALIZED) // Game initialized
                return true;
        }
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

void Client::sendPacket(sf::Packet &packet)
{
    if(send(packet, serverAddress, Server::PORT)
       != sf::Socket::Done)
        throw GameException("Cannot contact server");
}

void Client::onPacketReceived(sf::Packet &packet,
                              const sf::IpAddress &ipAddress,
                              unsigned short port)
{
    (void) port;
    (void) ipAddress;

    PacketType ptype = PacketFactory::GetPacketType(packet);
    if(ptype == PT_CONNECTION_ACK && state == CS_CREATED)
    {
        state = CS_CONNECTED_NO_MAP;

        std::cout << "Successfully connected to " << ipAddress << std::endl;
    }
    else if(ptype == PT_MAP_ANS && state == CS_CONNECTED_NO_MAP)
    {
        state = CS_MAPOK_SEND_INFOS;
        packet >> map;

        std::cout << "Received map from " << ipAddress << std::endl;

        // Send formation to server
        sf::Packet infoPacket;
        PacketFactory::BuildFormationPushPacket(infoPacket,
                                                formation);
        sendPacket(infoPacket);
    }
    else if(ptype == PT_FORMATION_ACK && state == CS_MAPOK_SEND_INFOS)
    {
        state = CS_INITIALIZED;

        std::cout << "Game initialized!" << std::endl;
    }
}

