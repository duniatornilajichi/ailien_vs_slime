#ifndef PENEMYGRAPHICSITEM_H
#define PENEMYGRAPHICSITEM_H

#include "model/entity/enemyentity.h"
#include "view/graphicsItem/enemygraphicsitem.h"
#include <QGraphicsPixmapItem>
#include <QPixmap>

class PEnemyGraphicsItem : public EnemyGraphicsItem {
    Q_OBJECT
public:
    PEnemyGraphicsItem(QSharedPointer<EnemyEntity> entity, QGraphicsItem *parent = nullptr);
};

#endif // PENEMYGRAPHICSITEM_H
