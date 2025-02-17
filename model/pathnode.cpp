#include "pathnode.h"

PathNode::PathNode(QSharedPointer<Block> block, int x, int y)
    :x(x), y(y), block(block) {
    f = block->getValue();
} ;
