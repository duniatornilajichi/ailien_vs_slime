#include "pathfinderadapter.h"
#include "pathfinder_class.h"

PathFinderAdapter::PathFinderAdapter(const QList<QList<QSharedPointer<Block>>> matrixBlocks)
    : nodeGrid(createNodeGrid(matrixBlocks)),
    comparator([](const PathNode& a, const PathNode& b) {return a.f > b.f;}),
    costFunction([this](const PathNode& a, const PathNode& b) -> float {
        float diagCost = a.getXPos() != b.getXPos() && a.getYPos() != b.getYPos() ? 1000 : 0 + (b.getUnderlyingBlock()->isSteppable() ? 0 : 1000);
        float baseCost = std::fabs(a.getUnderlyingBlock()->getEnergy() - b.getUnderlyingBlock()->getEnergy())*100 ;
        float enemyCost = 0.0f;

        for (const PathNode& enemy : enemies) {
            float distanceToEnemy = std::abs(b.getXPos() - enemy.getXPos()) +
                                    std::abs(b.getYPos() - enemy.getYPos());

            if (distanceToEnemy < STRANGER_DANGER) {
                enemyCost += (STRANGER_DANGER - distanceToEnemy) * ENEMY_WEIGHT*10;
            }
        }
        return diagCost+baseCost+enemyCost;
    }),
    distanceFunction([](const PathNode& a, const PathNode& b) {
        return std::abs(a.getXPos() - b.getXPos()) + std::abs(a.getYPos() - b.getYPos());
    }),  // Added missing comma here
    pathFinder(nodeGrid,
               nullptr,
               nullptr,
               comparator,
               matrixBlocks[0].size(),
               costFunction,
               distanceFunction,
               1.0f)
{
    QList<PathNode> enemyNodes;

    for (int y = 0; y < matrixBlocks.size(); ++y) {
        for (int x = 0; x < matrixBlocks[0].size(); ++x) {
            QSharedPointer<Entity> blockEntity = matrixBlocks[y][x]->getEntity();
            if (blockEntity) {
                EntityType type = blockEntity->getType();
                if (type == EntityType::ENEMY || type == EntityType::X_ENEMY || type == EntityType::P_ENEMY) {
                    enemyNodes.append(*QSharedPointer<PathNode>::create(matrixBlocks[y][x], x, y));
                }
            }
        }
    }

    setEnemyList(enemyNodes);
    qDebug() << "initalising PathAdapter";
}


std::vector<int> PathFinderAdapter::findPath(QSharedPointer<PathNode> start, QSharedPointer<PathNode> target) {
    pathFinder.setStart(start.get());
    pathFinder.setDestination(target.get());
    return pathFinder.A_star();
}


std::vector<PathNode> PathFinderAdapter::createNodeGrid(QList<QList<QSharedPointer<Block>>> matrixBlocks) {
    std::vector<PathNode> nodeGrid;
    int height = matrixBlocks.size();
    int width = matrixBlocks[0].size();

    nodeGrid.reserve(height * width);

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            auto node = QSharedPointer<PathNode>::create(matrixBlocks[y][x], x, y);
            nodeGrid.push_back(*node);
        }
    }

    return nodeGrid;
}
