#ifndef SNAPSHOT_H
#define SNAPSHOT_H

#include <map>

#include <SFML/Network.hpp>

#include <Entity.h>

class Snapshot
{
    public:
        Snapshot();
        virtual ~Snapshot();

        void AddEntity(const Entity &entity);

        const std::map<EntityID, Entity*> &GetEntities() const;

        friend sf::Packet &operator<<(sf::Packet &packet,
                                      const Snapshot &snapshot);
        friend sf::Packet &operator>>(sf::Packet &packet, Snapshot &snapshot);

    protected:
        std::map<EntityID, Entity*> entities;

};

#endif

