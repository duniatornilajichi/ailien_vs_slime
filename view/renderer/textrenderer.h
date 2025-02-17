#ifndef TEXTRENDERER_H
#define TEXTRENDERER_H

#include "../gamescene.h"
class TextRenderer
{
public:
    // TextRenderer();
    static void populateScene(GameScene *scene, QSharedPointer<GameWorld> gameWorld);
};

#endif // TEXTRENDERER_H
