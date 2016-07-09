#ifndef CLIENT_H
#define CLIENT_H

#include <SFML/Network.hpp>

#include <Map.h>
#include <Formation.h>
#include <SnapshotHistory.h>

enum LocalState
{
    LS_CREATED,
    LS_CONNECTED_NO_MAP,
    LS_MAPOK_SEND_INFOS,
    LS_INITIALIZED
};

class Client : protected sf::UdpSocket
{
    public:
        Client(const sf::IpAddress &serverAddress, EntityManager &entityManager,
               Map &map, Formation &formation);
        virtual ~Client();

        bool Connect();
        
        bool WaitForConnectionAck(const sf::Time &timeout);
        bool WaitForMap(const sf::Time &timeout);
        bool WaitForInfoTransferred(const sf::Time &timeout);
        
        bool Receive();

    protected:
        void sendPacket(sf::Packet &packet);
        void onPacketReceived(sf::Packet &packet,
                              const sf::IpAddress &ipAddress,
                              unsigned short port);

        LocalState state;
        sf::IpAddress serverAddress;
        
        SnapshotHistory snapshotHistory;

        EntityManager &entityManager;
        Map &map;
        Formation &formation;
};

#endif

