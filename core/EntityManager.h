#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include <map>
#include <vector>
#include <functional>

#include <Entity.h>
#include <Planet.h>
#include <SpaceShip.h>
#include <Snapshot.h>
#include <Map.h>

class EntityManager
{
    public:
        EntityManager();
        virtual ~EntityManager();

        Planet *AddPlanet(float density, float radius);
        SpaceShip *AddSpaceShip(float mass);

        void FindEntities(std::vector<Entity*> &entityCollection,
                          const std::vector<EntityID> &ids) const;

        void AddToSnapshot(Snapshot &snapshot) const;
        void RewriteEntities(const Snapshot &snapshot);

        void ApplyGravity(const Map &map);

    protected:
        EntityID getNextID();

        std::map<EntityID, Entity*> entities;
        EntityID currentID;

        friend class ControllerEntityManager;
        friend class ViewEntityManager;
        friend class ViewTracks;
};

#endif

