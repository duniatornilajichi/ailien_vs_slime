#include "tilegraphicsitem.h"

TileGraphicsItem::TileGraphicsItem(int size, QColor color)
    : size(size), color(color)
{}

QRectF TileGraphicsItem::boundingRect() const
{
    return QRectF(0, 0, size, size);
}

void TileGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    QRectF rect = boundingRect();
    painter->fillRect(rect, color);
    painter->setPen(Qt::NoPen);
    painter->drawRect(rect);
}
