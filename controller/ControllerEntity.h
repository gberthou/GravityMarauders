#ifndef CONTROLLER_ENTITY_H
#define CONTROLLER_ENTITY_H

#include <Entity.h>

class ControllerEntity
{
    public:
        explicit ControllerEntity(Entity &e);
        virtual ~ControllerEntity();

        void Update();

    protected:
        Entity &entity;
};

#endif

