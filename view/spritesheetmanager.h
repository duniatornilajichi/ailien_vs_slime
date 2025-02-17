#ifndef SPRITESHEETMANAGER_H
#define SPRITESHEETMANAGER_H

#include "model/behaviour.h"
#include <QVector>
#include <QPixmap>
#include <QImage>
#include <QRect>

class SpriteSheetManager {

public:
    SpriteSheetManager(const QString& path, int spriteWidth, int spriteHeight, std::vector<int> spritesPerRow);
    QPixmap getSprite(int row, int column) const;
    QVector<QPixmap> getSpriteFrames(PlayerBehaviour state) const;

private:
    QPixmap spritesheet;
    int spriteWidth;
    int spriteHeight;
    std::vector<int> spritesPerRow;
};


#endif // SPRITESHEETMANAGER_H
