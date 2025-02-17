#ifndef HEALTHPACKGRAPHICSITEM_H
#define HEALTHPACKGRAPHICSITEM_H

#include "model/entity/healthpackentity.h"
#include <QGraphicsPixmapItem>
#include <QPixmap>

class HealthpackGraphicsItem : public QGraphicsPixmapItem {
public:
    HealthpackGraphicsItem(QSharedPointer<HealthpackEntity> entity, QGraphicsItem *parent = nullptr);

    QRectF boundingRect() const override;

private:
    QPixmap sprite;
    int size{40};
};

#endif // HEALTHPACKGRAPHICSITEM_H
