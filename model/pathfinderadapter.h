#ifndef PATHFINDERADAPTER_H
#define PATHFINDERADAPTER_H

#include "model/pathnode.h"
#include <QObject>
#include "pathfinder_class.h"

class PathFinderAdapter : public QObject
{
    Q_OBJECT
public:
    PathFinderAdapter(QList<QList<QSharedPointer<Block>>> matrixBlocks);

    std::vector<int> findPath(QSharedPointer<PathNode> start, QSharedPointer<PathNode> target);

    inline std::vector<PathNode> getNodeGrid() const { return nodeGrid; };
    inline void setEnemyList(QList<PathNode> newEnemyList) { enemies = newEnemyList; };

    // bool isBlockedByEnemy(const int x, const int y);

private:
    std::vector<PathNode> nodeGrid;
    QList<PathNode> enemies;

    Comparator<PathNode> comparator;
    helper_func<PathNode> costFunction;
    helper_func<PathNode> distanceFunction;

    PathFinder<PathNode, PathNode> pathFinder;

    std::vector<PathNode> createNodeGrid(QList<QList<QSharedPointer<Block>>> matrixBlocks);

    const float STRANGER_DANGER = 5.0f;
    const float ENEMY_WEIGHT = 5.0f;
    const float PENEMY_WEIGHT = 10.0f;
    const float PTERRAIN_WEIGHT = 3.0f;
    const float XENEMY_WEIGHT = 15.0f;


};

#endif // PATHFINDERADAPTER_H
