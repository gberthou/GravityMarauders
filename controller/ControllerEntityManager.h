#ifndef CONTROLLER_ENTITY_MANAGER_H
#define CONTROLLER_ENTITY_MANAGER_H

#include <EntityManager.h>

class ControllerEntityManager
{
    public:
        explicit ControllerEntityManager(EntityManager &em);
        virtual ~ControllerEntityManager();

        void Update() const;

    protected:
        EntityManager &entityManager;
};

#endif

