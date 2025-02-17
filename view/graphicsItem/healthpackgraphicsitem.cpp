#include "healthpackgraphicsitem.h"
#include "view/spritesheetmanager.h"

HealthpackGraphicsItem::HealthpackGraphicsItem(QSharedPointer<HealthpackEntity> entity, QGraphicsItem *parent): QGraphicsPixmapItem(parent) {
    auto spriteManager = SpriteSheetManager(":/images/HEALTHPACK.png", 64, 64, {2});
    if (entity->isFull())
        sprite = spriteManager.getSprite(0, 0);
    else
        sprite = spriteManager.getSprite(0, 1);

    setPixmap(sprite);
}

QRectF HealthpackGraphicsItem::boundingRect() const
{
    return QRectF(0, 0, size, size);
}

