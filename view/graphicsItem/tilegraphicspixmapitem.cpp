#include "tilegraphicspixmapitem.h"

TileGraphicsPixmapItem::TileGraphicsPixmapItem(int size, QPixmap pixmap, QGraphicsItem *parent): QGraphicsPixmapItem(parent) {
    this->size = size;
    sprite = pixmap;
    if (sprite.isNull()) {
        qDebug() << "Failed to load healthpack image!";
        return;
    }
    sprite = sprite.scaled(size, size, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    setPixmap(sprite);
}

QRectF TileGraphicsPixmapItem::boundingRect() const
{
    return QRectF(0, 0, size, size);
}
