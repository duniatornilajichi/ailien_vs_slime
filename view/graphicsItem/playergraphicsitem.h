#ifndef PLAYERGRAPHICSITEM_H
#define PLAYERGRAPHICSITEM_H

#include "model/behaviour.h"
#include "model/player.h"
#include "qtimer.h"
#include "view/spritesheetmanager.h"
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QPropertyAnimation>

class PlayerGraphicsItem : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
    // Q_PROPERTY(QPointF pos READ pos WRITE setPos NOTIFY)
public:
    PlayerGraphicsItem(QSharedPointer<Player> player, QGraphicsItem *parent = nullptr);
    void updateSprite(PlayerBehaviour state); // might be not needed
    void setPosition(int x, int y);

private slots:
    void handleAnimation();
private:
    //QPixmap sprite;
    SpriteSheetManager playerManager;
    QTimer animationTimer; // this sends signal to our private slot
    //QMap<PlayerBehaviour, QPixmap> sprites;
    QVector<QPixmap> currentAnimation;
    int currentFrame{0};

    int size{40};
    void loadSprites();

    QSharedPointer<Player> player;
};

#endif // PLAYERGRAPHICSITEM_H
