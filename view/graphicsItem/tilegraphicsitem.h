#ifndef TILEGRAPHICSITEM_H
#define TILEGRAPHICSITEM_H

#include <QGraphicsItem>
#include <QPainter>

class TileGraphicsItem : public QGraphicsItem {
public:
    TileGraphicsItem(int size, QColor color = Qt::darkMagenta);

    inline void setTileColor(QColor newColor) { color = newColor; };

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    int size;
    QColor color;
};

#endif // TILEGRAPHICSITEM_H
