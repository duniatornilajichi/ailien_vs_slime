#ifndef PTERRAINGRAPHICSITEM_H
#define PTERRAINGRAPHICSITEM_H

#include "view/graphicsItem/enemygraphicsitem.h"
#include <QGraphicsPixmapItem>
#include <QPixmap>

class PTerrainGraphicsItem : public EnemyGraphicsItem {
    Q_OBJECT
public:
    PTerrainGraphicsItem(QGraphicsItem *parent = nullptr);
};

#endif // PTERRAINGRAPHICSITEM_H
