#include "pterraingraphicsitem.h"

PTerrainGraphicsItem::PTerrainGraphicsItem(QGraphicsItem *parent) : EnemyGraphicsItem(nullptr, parent) {
    spriteManager = SpriteSheetManager(":/images/P_TERRAIN.png", 40, 40, {2});
    updateSprite();
}
