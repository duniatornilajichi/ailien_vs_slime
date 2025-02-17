#ifndef OVERLAYRENDERER_H
#define OVERLAYRENDERER_H

#include "model/gameworld.h"
#include "../gamescene.h"
class OverlayRenderer
{
public:
    // OverlayRenderer();
    static void populateScene(GameScene *scene, QSharedPointer<GameWorld> gameWorld);
    // QPixmap pixelValueToPixmap(float pixelValue);
};


#endif // OVERLAYRENDERER_H
