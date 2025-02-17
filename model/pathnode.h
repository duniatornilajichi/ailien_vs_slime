#ifndef PATHNODE_H
#define PATHNODE_H

#include "model/block.h"
#include "model/entity/entity.h"
class PathNode
{
public:
    PathNode() = default;
    PathNode(QSharedPointer<Block> block, int x, int y);

    inline int getXPos() const { return x; }
    inline int getYPos() const { return y; }
    inline float getValue() const { return block->getValue(); }

    float f{0.0f};
    float g{0.0f};
    float h{0.0f};
    bool visited{false};
    bool closed{false};
    PathNode* prev{nullptr};

    inline bool isWalkable() const {
        return block->isSteppable() &&
               (!block->getEntity() ||
                block->getEntity()->getType() != EntityType::ENEMY);
    }

    inline QSharedPointer<Block> getUnderlyingBlock() const { return block; };

private:
    int x;
    int y;
    QSharedPointer<Block> block;

};

#endif // PATHNODE_H
