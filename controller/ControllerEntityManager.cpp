#include <ControllerEntityManager.h>
#include <ControllerEntity.h>

ControllerEntityManager::ControllerEntityManager(EntityManager &em):
    entityManager(em)
{
}

ControllerEntityManager::~ControllerEntityManager()
{
}

void ControllerEntityManager::Update() const
{
    for(auto it : entityManager.entities)
        ControllerEntity(*it.second).Update();
}

