#include "penemygraphicsitem.h"

PEnemyGraphicsItem::PEnemyGraphicsItem(QSharedPointer<EnemyEntity> entity, QGraphicsItem *parent) : EnemyGraphicsItem(entity, parent) {
    spriteManager = SpriteSheetManager(":/images/P_ENEMY.png", 32, 32, {4, 4});
    updateSprite();
}
