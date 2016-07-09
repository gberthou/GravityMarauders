#ifndef CONTROLLER_ENTITY_MANAGER_H
#define CONTROLLER_ENTITY_MANAGER_H

#include <EntityManager.h>

class ControllerEntityManager
{
    public:
        ControllerEntityManager(EntityManager &entityManager);
        virtual ~ControllerEntityManager();

        void Update();

    protected:
        EntityManager &entityManager;
};

#endif

