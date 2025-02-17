#include "spritesheetmanager.h"
#include "qdebug.h"

SpriteSheetManager::SpriteSheetManager(const QString& path, int spriteWidth, int spriteHeight, std::vector<int> spritesPerRow)
    : spriteWidth(spriteWidth), spriteHeight(spriteHeight), spritesPerRow(spritesPerRow) {
    spritesheet = QPixmap(path);
    if (spritesheet.isNull()) {
        qDebug() << "Pixmap is a null pixmap";
    }
}

QPixmap SpriteSheetManager::getSprite(int row, int column) const {
    QPixmap sprite = spritesheet.copy(column*spriteWidth, row*spriteHeight, spriteWidth, spriteHeight)
        .scaled(40, 40, Qt::KeepAspectRatio, Qt::SmoothTransformation); // change back to 40, 40;
    return sprite;
}

QVector<QPixmap> SpriteSheetManager::getSpriteFrames(PlayerBehaviour state) const {
    QVector<QPixmap> frames;

    for (int i=0; i<spritesPerRow[state]; i++) { // adjust the number of frames from the sprite sheet!!
        QPixmap frame = getSprite(state,i);
        frames.push_back(frame);
    }

    return frames;
}
