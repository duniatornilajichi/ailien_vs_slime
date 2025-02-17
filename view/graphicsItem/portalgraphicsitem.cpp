#include "portalgraphicsitem.h"

PortalGraphicsItem::PortalGraphicsItem(QGraphicsItem *parent) : EnemyGraphicsItem(nullptr, parent) {
    spriteManager = SpriteSheetManager(":/images/PORTAL.png", 32, 32, {8});
    updateSprite();
}
