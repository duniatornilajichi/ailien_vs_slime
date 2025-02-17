#ifndef TILEGRAPHICSPIXMAPITEM_H
#define TILEGRAPHICSPIXMAPITEM_H

#include <QGraphicsItem>
#include <QPainter>

class TileGraphicsPixmapItem : public QGraphicsPixmapItem {
public:
    TileGraphicsPixmapItem(int size, QPixmap pixmap, QGraphicsItem *parent = nullptr);

    QRectF boundingRect() const override;

private:
    QPixmap sprite;
    int size{40};
};

#endif // TILEGRAPHICSPIXMAPITEM_H
