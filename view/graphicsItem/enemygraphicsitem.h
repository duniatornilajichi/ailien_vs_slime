#ifndef ENEMYGRAPHICSITEM_H
#define ENEMYGRAPHICSITEM_H

#include "model/entity/enemyentity.h"
#include "qpropertyanimation.h"
#include "qtimer.h"
#include "view/spritesheetmanager.h"
#include <QGraphicsPixmapItem>
#include <QPixmap>

class EnemyGraphicsItem : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    EnemyGraphicsItem(QSharedPointer<EnemyEntity> entity, QGraphicsItem *parent = nullptr);

    void updateSprite();

    QRectF boundingRect() const override;

private slots:
    virtual void handleAnimation();

protected:
    SpriteSheetManager spriteManager;
    QTimer animationTimer; // this sends signal to our private slot
    QVector<QPixmap> currentAnimation;
    int currentFrame{0};
    QSharedPointer<EnemyEntity> entity;

    int size{40};
    void loadSprites();

    QPropertyAnimation* moveAnimation{nullptr};
};

#endif // ENEMYGRAPHICSITEM_H
