#include "enemygraphicsitem.h"
#include "model/entity/enemyentity.h"

EnemyGraphicsItem::EnemyGraphicsItem(QSharedPointer<EnemyEntity> entity, QGraphicsItem *parent)
    : QObject(), QGraphicsPixmapItem(parent), spriteManager(SpriteSheetManager(":/images/ENEMY.png", 32, 32, {4, 4})) {
    this->entity = entity;
    updateSprite();

    connect(&animationTimer, SIGNAL(timeout()), this, SLOT(handleAnimation()));
}

void EnemyGraphicsItem::loadSprites() {

    QPixmap initialSprite = spriteManager.getSprite(0, 0);
    setPixmap(initialSprite);
}

QRectF EnemyGraphicsItem::boundingRect() const
{
    return QRectF(0, 0, size, size);
}

void EnemyGraphicsItem::updateSprite() {
    QVector<QPixmap> newFrames = spriteManager.getSpriteFrames(entity && !entity->isAlive() ? Behaviour::MOVE : Behaviour::IDLE);

    if (newFrames.isEmpty()) return;

    if (!newFrames.isEmpty()) {
        currentAnimation = newFrames;
        currentFrame = entity && !entity->isAlive() ? currentAnimation.size()-1 : 0;
        setPixmap(currentAnimation[currentFrame]);

        if (currentAnimation.size() > 1) {
            if (!animationTimer.isActive()) {
                animationTimer.start(100);
            }
        }
    }

    if (currentAnimation.size()>1) {
        currentFrame = entity && !entity->isAlive() ? currentAnimation.size()-1 : 0;
        animationTimer.start(100);  // 100ms per frame
    } else {
        if (!currentAnimation.isEmpty()) {
            animationTimer.stop();
            setPixmap(currentAnimation[0]);
        }
    }

}

void EnemyGraphicsItem::handleAnimation() {
    if (currentAnimation.isEmpty()) return;
    if (entity && !entity->isAlive() && currentFrame == currentAnimation.size()-1) {
        setPixmap(currentAnimation[currentAnimation.size()-1]);
    } else {
        currentFrame = (currentFrame+1) % currentAnimation.size();
        setPixmap(currentAnimation[currentFrame]);
    }
}

