#ifndef COLORRENDERER_H
#define COLORRENDERER_H

#include "../gamescene.h"

class ColorRenderer
{
public:
    // ColorRenderer() {};
    static void populateScene(GameScene *scene, QSharedPointer<GameWorld> gameWorld);

    static QColor pixelValueToHSV(float pixelValue);
};

#endif // COLORRENDERER_H
