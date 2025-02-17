#include "view/gamescene.h"
#include <QSharedPointer>
#include "qpainter.h"
#include "renderer/colorrenderer.h"
#include "renderer/overlayrenderer.h"
#include "renderer/textrenderer.h"

void GameScene::createScene()
{
    if (!gameWorld) return;

    switch (viewType) {
    case 0:
        ColorRenderer::populateScene(this, gameWorld);
        break;
    case 1:
        TextRenderer::populateScene(this, gameWorld);
        break;
    case 2:
        OverlayRenderer::populateScene(this, gameWorld);
        break;
    }
}

void GameScene::setViewType(int newType){
    clear();
    viewType = newType;
    createScene();
}

void GameScene::updateWorld(QSharedPointer<GameWorld> world){
    clear();
    gameWorld = world;
    createScene();
    emit update();
}


void GameScene::highlightPath(std::queue<Direction> pathCopy) {
    if (pathCopy.empty()) return;
    QSharedPointer<Player> m_player = gameWorld->getPlayer();
    if (!v_player) return;

    x_start = m_player->getX();
    y_start = m_player->getY();

    path = pathCopy;

    showingHighlights = true;

    update();
    emit highlightDone();
}
