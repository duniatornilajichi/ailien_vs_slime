#include "energypackgraphicsitem.h"
#include "view/spritesheetmanager.h"

EnergypackGraphicsItem::EnergypackGraphicsItem(QSharedPointer<EnergyPackEntity> entity, QGraphicsItem *parent): QGraphicsPixmapItem(parent) {
    auto spriteManager = SpriteSheetManager(":/images/ENERGYPACK.png", 40, 40, {2});
    if (entity->isFull())
        sprite = spriteManager.getSprite(0, 0);
    else
        sprite = spriteManager.getSprite(0, 1);

    setPixmap(sprite);
}

QRectF EnergypackGraphicsItem::boundingRect() const
{
    return QRectF(0, 0, size, size);
}
