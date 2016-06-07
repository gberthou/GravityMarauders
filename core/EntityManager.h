#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include <map>
#include <vector>

#include <Entity.h>
#include <Planet.h>
#include <SpaceShip.h>
#include <Snapshot.h>

class EntityManager
{
    public:
        EntityManager();
        virtual ~EntityManager();

        Planet *AddPlanet(float density, float radius);
        SpaceShip *AddSpaceShip(float mass);

        void FindEntities(std::vector<Entity*> &entities,
                          const std::vector<EntityID> &ids);

        void AddToSnapshot(Snapshot &snapshot) const;

    protected:
        EntityID getNextID();

        std::map<EntityID, Entity*> entities;
        EntityID currentID;
};

#endif

