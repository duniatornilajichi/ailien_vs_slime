#ifndef XENEMYGRAPHICSITEM_H
#define XENEMYGRAPHICSITEM_H

#include "view/graphicsItem/enemygraphicsitem.h"
#include <QGraphicsPixmapItem>
#include <QPixmap>

class XEnemyGraphicsItem : public EnemyGraphicsItem {
    Q_OBJECT
public:
    XEnemyGraphicsItem(QSharedPointer<EnemyEntity> entity, QGraphicsItem *parent = nullptr);
};

#endif // XENEMYGRAPHICSITEM_H
