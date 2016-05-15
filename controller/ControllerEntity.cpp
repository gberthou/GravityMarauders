#include <ControllerEntity.h>

ControllerEntity::ControllerEntity(Entity &e):
    entity(e)
{
}

ControllerEntity::~ControllerEntity()
{
}

void ControllerEntity::Update()
{
    entity.UpdatePhysics();
}

