#ifdef SERVER
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

Server::Server(EntityManager &em, const Map &m):
    entityManager(em),
    map(m)
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

void Server::SpawnFormation(const Formation &formation,
                            std::vector<Entity*> &entities)
{
    formation.Spawn(entityManager, entities);
}

void Server::sendPacket(sf::Packet &packet, const sf::IpAddress &ipAddress,
                        unsigned short port)
{
    if(send(packet, ipAddress, port) != sf::Socket::Done)
        throw GameException("Cannot send packet to client");
}

void Server::onPacketReceived(sf::Packet &packet,
                              const sf::IpAddress &ipAddress,
                              unsigned short port)
{
    PacketType ptype = PacketFactory::GetPacketType(packet);
    if(ptype == PT_CONNECTION_REQ)
    {
        // Add client to the list of clients
        std::pair<ClientDesc, ClientContent>
            pair(ClientDesc{ipAddress, port}, ClientContent{CS_WAIT_INFO, Formation(sf::Vector2f())});
        if(clients.insert(pair).second) // New client
        {
            std::cout << '[' << ipAddress << ':' << port
                      << "] is now connected!" << std::endl;
        }

        // Send connection ack packet
        sf::Packet response;
        PacketFactory::BuildConnectionAckPacket(response);
        sendPacket(response, ipAddress, port);
    }
    else if(ptype == PT_MAP_REQ)
    {
        auto it = clients.find({ipAddress, port});
        if(it != clients.end())
        {
            sf::Packet response;
            PacketFactory::BuildMapAnsPacket(response, map);
            sendPacket(response, ipAddress, port);
        }
    }
    else if(ptype == PT_FORMATION_PUSH)
    {
        auto it = clients.find({ipAddress, port});
        if(it != clients.end() && it->second.state != CS_SPAWNED)
        {
            // Update matching formation
            packet >> it->second.formation;

            // Send ack 
            sf::Packet response;
            PacketFactory::BuildFormationAckPacket(response);
            sendPacket(response, ipAddress, port);
        }
    }
    else if(ptype == PT_SPAWN_PUSH)
    {
        auto it = clients.find({ipAddress, port});
        if(it != clients.end() && it->second.state != CS_SPAWNED)
        {
            std::vector<Entity*> spawnedEntities;
            SpawnFormation(it->second.formation, spawnedEntities);

            it->second.state = CS_SPAWNED;

            // Create snapshot
            Snapshot snapshot;
            entityManager.AddToSnapshot(snapshot); 

            // Send ack
            sf::Packet response;
            PacketFactory::BuildSpawnAckPacket(response, snapshot,
                                               spawnedEntities);
            sendPacket(response, ipAddress, port);
        }
    }
}

#endif

