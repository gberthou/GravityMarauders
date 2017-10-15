#ifndef SERVER_H
#define SERVER_H

#include <map>
#include <vector>

#include <SFML/Network.hpp>

#include <Map.h>
#include <Formation.h>
#include <EntityManager.h>

enum ClientState
{
    CS_WAIT_INFO,
    CS_SPAWNED
};

struct ClientDesc
{
    sf::IpAddress ip;
    unsigned short port;
};

struct ClientContent
{
    ClientState state;
    Formation formation;
};

bool operator<(const ClientDesc & c1, const ClientDesc &c2);

class Server : protected sf::UdpSocket
{
    public:
        Server(EntityManager &em, const Map &m);
        virtual ~Server();

        bool Receive();

        void SpawnFormation(const Formation &formation,
                            std::vector<Entity*> &entities);

        static const unsigned short PORT = 41337;

    protected:
        void sendPacket(sf::Packet &packet, const sf::IpAddress &ipAddress,
                        unsigned short port);
        void onPacketReceived(sf::Packet &packet,
                              const sf::IpAddress &ipAddress,
                              unsigned short port);

        std::map<ClientDesc, ClientContent> clients;
        
        EntityManager &entityManager;
        const Map &map;
};

#endif

