#include <SnapshotHistory.h>

SnapshotHistory::SnapshotHistory(EntityManager &emanager):
    entityManager(emanager)
{
}

SnapshotHistory::~SnapshotHistory()
{
}

void SnapshotHistory::AddSnapshot(const Snapshot *snapshot)
{
    while(snapshots.size() >= HISTORY_SIZE)
        snapshots.pop();
    snapshots.push(snapshot);
}

