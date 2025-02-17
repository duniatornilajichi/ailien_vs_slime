#ifndef ENERGYPACKGRAPHICSITEM_H
#define ENERGYPACKGRAPHICSITEM_H

#include "model/entity/energypackentity.h"
#include <QGraphicsPixmapItem>
#include <QPixmap>

class EnergypackGraphicsItem : public QGraphicsPixmapItem {
public:
    EnergypackGraphicsItem(QSharedPointer<EnergyPackEntity> entity, QGraphicsItem *parent = nullptr);

    QRectF boundingRect() const override;

private:
    QPixmap sprite;
    int size{40};
};

#endif // ENERGYPACKGRAPHICSITEM_H
