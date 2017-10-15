#ifndef SNAPSHOT_HISTORY_H
#define SNAPSHOT_HISTORY_H

#include <queue>

#include <Snapshot.h>
#include <EntityManager.h>

class SnapshotHistory
{
    public:
        explicit SnapshotHistory(EntityManager &em);
        virtual ~SnapshotHistory();

        void AddSnapshot(const Snapshot *snapshot);

    protected:
        static const unsigned int HISTORY_SIZE = 4;

        std::queue<const Snapshot*> snapshots;
        EntityManager &entityManager;
};

#endif

