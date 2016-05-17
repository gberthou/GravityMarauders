#include <Snapshot.h>

Snapshot::Snapshot()
{
}

Snapshot::~Snapshot()
{
}

unsigned int Snapshot::AddEntity(const Entity &entity)
{
    unsigned int id = NewEntityId();
    std::pair<unsigned int, Entity> pair(id, entity);
    entities.insert(pair);

    return id;
}

unsigned int Snapshot::NewEntityId() const
{
    auto it = entities.crbegin();
    if(it != entities.crend())
    {
        unsigned int attempt = it->first + 1;

        // Should end some day
        while(entities.find(attempt) != entities.end())
            ++attempt;
        return attempt;
    }

    // Map is initially empty, create Id 0
    return 0; 
}

