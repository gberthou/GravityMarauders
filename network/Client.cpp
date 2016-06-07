#ifndef SERVER
#include <iostream>

#include <Client.h>
#include <Server.h>
#include <PacketFactory.h>
#include <GameException.h>

Client::Client(const sf::IpAddress &sAddress, EntityManager &emanager, Map &m,
               Formation &f):
    state(LS_CREATED),
    serverAddress(sAddress),
    entityManager(emanager),
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
    if(state == LS_CREATED)
    {
        return true;
    }
    return false;
}

bool Client::WaitForConnectionAck(const sf::Time &timeout)
{
    const unsigned int ATTEMPT_COUNT = 10;

    if(state == LS_CREATED)
    {
        for(unsigned int i = 0; i < ATTEMPT_COUNT; ++i)
        {
            sf::Packet packet;
            PacketFactory::BuildConnectionReqPacket(packet);
            sendPacket(packet);
            
            sf::SocketSelector selector;
            selector.add(*this);
            if(selector.wait(timeout / static_cast<float>(ATTEMPT_COUNT)))
            {
                Receive();
                if(state == LS_CONNECTED_NO_MAP) // Connection accepted
                {
                    sf::Packet mapReq;
                    PacketFactory::BuildMapReqPacket(mapReq);
                    sendPacket(mapReq);
                    return true;
                }
            }
        }
    }
    return false;
}

bool Client::WaitForMap(const sf::Time &timeout)
{
    if(state == LS_CONNECTED_NO_MAP)
    {
        sf::SocketSelector selector;
        selector.add(*this);
        if(selector.wait(timeout))
        {
            Receive();
            if(state == LS_MAPOK_SEND_INFOS) // Map received
                return true;
        }
    }
    return false;
}

bool Client::WaitForInfoTransferred(const sf::Time &timeout)
{
    if(state == LS_MAPOK_SEND_INFOS)
    {
        sf::SocketSelector selector;
        selector.add(*this);
        if(selector.wait(timeout))
        {
            Receive();
            if(state == LS_INITIALIZED) // Game initialized
                return true;
        }
    }
    return false;
}

bool Client::Receive()
{
    sf::Socket::Status status;
    bool ret = false;

    do
    {
        sf::Packet packet;
        sf::IpAddress ipAddress;
        unsigned short port;
        
        status = receive(packet, ipAddress, port);

        if(status == sf::Socket::Done) // A packet has been received
        {
            onPacketReceived(packet, ipAddress, port);
            ret = true;
        }
        else if(status != sf::Socket::NotReady) // Error
        {
            throw GameException("Client::Receive has failed");
        }
    } while(status == sf::Socket::Done);
    return ret;
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
    if(ptype == PT_CONNECTION_ACK && state == LS_CREATED)
    {
        state = LS_CONNECTED_NO_MAP;

        std::cout << "Successfully connected to " << ipAddress << std::endl;
    }
    else if(ptype == PT_MAP_ANS && state == LS_CONNECTED_NO_MAP)
    {
        state = LS_MAPOK_SEND_INFOS;
        packet >> map;

        std::cout << "Received map from " << ipAddress << std::endl;

        // Send formation to server
        sf::Packet infoPacket;
        PacketFactory::BuildFormationPushPacket(infoPacket,
                                                formation);
        sendPacket(infoPacket);
    }
    else if(ptype == PT_FORMATION_ACK && state == LS_MAPOK_SEND_INFOS)
    {
        state = LS_INITIALIZED;
        std::cout << "Game initialized!" << std::endl;

        // Send spawn request
        sf::Packet spawnPacket;
        PacketFactory::BuildSpawnPushPacket(spawnPacket);

        sendPacket(spawnPacket);
    }
    else if(ptype == PT_SPAWN_ACK && state == LS_INITIALIZED)
    {
        Snapshot snapshot;
        packet >> snapshot;

        sf::Uint32 entityCount;
        std::vector<EntityID> spawnedEntitiesID;

        packet >> entityCount;
        std::cout << "There are " << entityCount << " entities" << std::endl;
        spawnedEntitiesID.resize(entityCount);
        for(sf::Uint32 i = 0; i < entityCount; ++i)
            packet >> spawnedEntitiesID[i];

        std::vector<Entity*> spawnedEntities;
        entityManager.FindEntities(spawnedEntities, spawnedEntitiesID);
    }
}

#endif

