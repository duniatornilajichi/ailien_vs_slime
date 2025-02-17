#include "damagegraphicsitem.h"

DamageGraphicsItem::DamageGraphicsItem(QGraphicsItem *parent) : EnemyGraphicsItem(nullptr, parent) {
    spriteManager = SpriteSheetManager(":/images/DAMAGE.png", 64, 64, {7});
    updateSprite();
}

void DamageGraphicsItem::handleAnimation() {
    if (currentAnimation.isEmpty()) return;
    currentFrame = (currentFrame+1 > currentAnimation.size()-1) ? (currentAnimation.size()-1) : (currentFrame+1);
    setPixmap(currentAnimation[currentFrame]);
}
