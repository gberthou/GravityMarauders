#ifndef SNAPSHOT_H
#define SNAPSHOT_H

#include <map>

#include <Entity.h>

class Snapshot
{
    public:
        Snapshot();
        virtual ~Snapshot();

        unsigned int AddEntity(const Entity &entity);
        unsigned int NewEntityId() const;

    protected:
        std::map<unsigned int, Entity> entities;

};

#endif

