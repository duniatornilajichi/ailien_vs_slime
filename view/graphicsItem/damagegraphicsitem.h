#ifndef DAMAGEGRAPHICSITEM_H
#define DAMAGEGRAPHICSITEM_H

#include "view/graphicsItem/enemygraphicsitem.h"
#include <QGraphicsPixmapItem>
#include <QPixmap>

class DamageGraphicsItem : public EnemyGraphicsItem {
    Q_OBJECT
public:
    DamageGraphicsItem(QGraphicsItem *parent = nullptr);

private slots:
    void handleAnimation() override;
};

#endif // DAMAGEGRAPHICSITEM_H
