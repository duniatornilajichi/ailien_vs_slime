#include "xenemygraphicsitem.h"

XEnemyGraphicsItem::XEnemyGraphicsItem(QSharedPointer<EnemyEntity> entity, QGraphicsItem *parent) : EnemyGraphicsItem(entity, parent) {
    spriteManager = SpriteSheetManager(":/images/X_ENEMY.png", 32, 32, {4, 4});
    updateSprite();
}
