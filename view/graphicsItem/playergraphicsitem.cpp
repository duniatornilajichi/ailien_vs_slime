#include "playergraphicsitem.h"
#include "view/spritesheetmanager.h"

#include <QTime>

PlayerGraphicsItem::PlayerGraphicsItem(QSharedPointer<Player> player, QGraphicsItem *parent)
    : QObject(), QGraphicsPixmapItem(parent), playerManager(SpriteSheetManager(":/images/PROTAGONIST_SHEET.png", 16, 16, {2, 3, 3, 3, 3})), player{player} {
    updateSprite(player->getCurrentState());
    connect(&animationTimer, SIGNAL(timeout()), this, SLOT(handleAnimation()));
}

//setPixmap(sprites[PlayerBehaviour::IDLE]);


void PlayerGraphicsItem::loadSprites() {
    QPixmap initialSprite = playerManager.getSprite(0, 0);
    setPixmap(initialSprite);
}

void PlayerGraphicsItem::setPosition(int x, int y) {
    //qDebug() << "Setting position in PlayerGraphicsItem:" << x << y;
    setPos(x,y);
    //TODO: check if view adaptation is required??
}

void PlayerGraphicsItem::updateSprite(PlayerBehaviour state) {
    //qDebug() << "\tupdateSprite called with state:" << static_cast<int>(state);
    QVector<QPixmap> newFrames = playerManager.getSpriteFrames(state);
    //qDebug() << " Got animation frames, size:" << newFrames.size();

    // for(int i = 0; i < newFrames.size(); i++) {
    //     qDebug() << "Frame" << i << "isNull:" << newFrames[i].isNull();
    // }

    if (newFrames.isEmpty()) return;

    if (!newFrames.isEmpty()) {
        currentAnimation = newFrames;
        currentFrame = 0;
        setPixmap(currentAnimation[currentFrame]);

        if (currentAnimation.size() > 1) {
            if (!animationTimer.isActive()) {
                animationTimer.start(100);
            }
        }
    }

    if (currentAnimation.size()>1) {
        currentFrame = 0;
        animationTimer.start(100);  // 100ms per frame
    } else {
        if (!currentAnimation.isEmpty()) {
            animationTimer.stop();
            setPixmap(currentAnimation[0]);
        }
    }

}

void PlayerGraphicsItem::handleAnimation() {
    if (currentAnimation.isEmpty()) return;

    if (player->getCurrentState() == PlayerBehaviour::ATTACKED || player->getCurrentState() == PlayerBehaviour::DIE)
        currentFrame = std::min((currentFrame+1), (int)(currentAnimation.size()-1));
    else
        currentFrame = (currentFrame+1) % currentAnimation.size();
    setPixmap(currentAnimation[currentFrame]);
    //qDebug() << "Current frame:" << currentFrame;
}

