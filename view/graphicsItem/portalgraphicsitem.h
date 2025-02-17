#ifndef PORTALGRAPHICSITEM_H
#define PORTALGRAPHICSITEM_H

#include "view/graphicsItem/enemygraphicsitem.h"
#include <QGraphicsPixmapItem>
#include <QPixmap>

class PortalGraphicsItem : public EnemyGraphicsItem {
    Q_OBJECT
public:
    PortalGraphicsItem(QGraphicsItem *parent = nullptr);
};

#endif // PORTALGRAPHICSITEM_H
