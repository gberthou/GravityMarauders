#include <EntityManager.h>
#include <GameException.h>

EntityManager::EntityManager():
    currentID({0, 1})
{
}

EntityManager::~EntityManager()
{
}

Planet *EntityManager::AddPlanet(float density, float radius)
{
    Planet *planet = new Planet(currentID, density, radius);
    if(planet == nullptr)
        throw GameException("Cannot allocate planet");

    entities.insert(std::pair<EntityID, Entity*>(currentID, planet));

    getNextID();
    return planet;
}

SpaceShip *EntityManager::AddSpaceShip(float mass)
{
    SpaceShip *spaceship = new SpaceShip(currentID, mass);

    if(spaceship == nullptr)
        throw GameException("Cannot allocate spaceship");

    entities.insert(std::pair<EntityID, Entity*>(currentID, spaceship));

    getNextID();
    return spaceship;
}

void EntityManager::FindEntities(std::vector<Entity*> &entityCollection,
                                 const std::vector<EntityID> &ids)
{
    entityCollection.clear();
    for(EntityID id : ids)
    {
        auto it = entities.find(id);
        if(it == entities.end())
            throw GameException("Trying to access a non-existing entity");
        entityCollection.push_back(it->second);
    }
}

void EntityManager::AddToSnapshot(Snapshot &snapshot) const
{
    for(auto it : entities)
        snapshot.AddEntity(*it.second);
}

void EntityManager::RewriteEntities(const Snapshot &snapshot)
{
    entities.clear();
    for(auto it : snapshot.GetEntities())
        entities.insert(std::pair<EntityID, Entity*>(it.first, it.second));
}

void EntityManager::ApplyGravity(const Map &map)
{
    for(auto it : entities)
        map.ApplyGravityTo(*it.second);
}

EntityID EntityManager::getNextID()
{
    do
    {
    } while(entities.find(++currentID) != entities.end()); 
    return currentID;
}

