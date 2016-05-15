#ifndef CONTROLLER_ENTITY_H
#define CONTROLLER_ENTITY_H

#include <Entity.h>

class ControllerEntity
{
    public:
        ControllerEntity(Entity &entity);
        virtual ~ControllerEntity();

        void Update();

    protected:
        Entity &entity;
};

#endif

