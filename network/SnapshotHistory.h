#ifndef SNAPSHOT_HISTORY_H
#define SNAPSHOT_HISTORY_H

#include <queue>

#include <Snapshot.h>

class SnapshotHistory
{
    public:
        SnapshotHistory();
        virtual ~SnapshotHistory();

        void AddSnapshot(const Snapshot &snapshot);

    protected:
        static const unsigned int HISTORY_SIZE = 4;

        std::queue<Snapshot> snapshots;
};

#endif

