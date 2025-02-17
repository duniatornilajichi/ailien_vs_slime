#include "view/graphicsItem/damagegraphicsitem.h"
#include "view/graphicsItem/enemygraphicsitem.h"
#include "view/graphicsItem/energypackgraphicsitem.h"
#include "view/graphicsItem/penemygraphicsitem.h"
#include "view/graphicsItem/portalgraphicsitem.h"
#include "view/graphicsItem/pterraingraphicsitem.h"
#include "view/graphicsItem/healthpackgraphicsitem.h"
#include "view/graphicsItem/tilegraphicspixmapitem.h"
#include "view/graphicsItem/xenemygraphicsitem.h"
#include <cmath>
#include "overlayrenderer.h"

QPixmap pixelValueToPixmap(BlockType type, SpriteSheetManager spriteManager) {
    QPixmap sprite;
    switch (type) {
    case BlockType::SMOOTH:
        sprite = spriteManager.getSprite(8, 0);
        break;
    case BlockType::PLAIN:
        sprite = spriteManager.getSprite(1, 0);
        break;
    case BlockType::ROUGH:
        sprite = spriteManager.getSprite(2, 0);
        break;
    case BlockType::OBSTACLE:
        sprite = spriteManager.getSprite(7, 0);
        break;
    case BlockType::WALL:
        sprite = spriteManager.getSprite(5, 0);
    }
    return sprite;
}

void OverlayRenderer::populateScene(GameScene *scene, QSharedPointer<GameWorld> gameWorld) {
    SpriteSheetManager spriteManager{":/images/OverlayTiles.png", 48, 48, {}};
    const int TILE_SIZE = 40;
    auto blocks = gameWorld->getMatrixBlocks();
    for (int i = 0; i < blocks.size(); i++) {
        for (int j = 0; j < blocks.at(i).size(); j++) {
            TileGraphicsPixmapItem *tile = new TileGraphicsPixmapItem(TILE_SIZE, pixelValueToPixmap(blocks.at(i).at(j)->getType(), spriteManager));
            tile->setPos(j * TILE_SIZE, i * TILE_SIZE);
            scene->addItem(tile);
        }
    }
    auto player = new PlayerGraphicsItem(gameWorld->getPlayer());
    for (auto entity : gameWorld->getEntities()) {
        if (entity->getType() == EntityType::P_TERRAIN) {
            auto *pterrain = new PTerrainGraphicsItem();
            pterrain->setPos((entity->getXPos())*TILE_SIZE, (entity->getYPos())*TILE_SIZE);
            scene->addItem(pterrain);
        } else if (entity->getType() == EntityType::HEALTHPACK) {
            auto *healthpack = new HealthpackGraphicsItem(qSharedPointerCast<HealthpackEntity>(entity));
            healthpack->setPos((entity->getXPos())*TILE_SIZE, (entity->getYPos())*TILE_SIZE);
            scene->addItem(healthpack);
        } else if (entity->getType() == EntityType::ENERGYPACK) {
            auto *healthpack = new EnergypackGraphicsItem(qSharedPointerCast<EnergyPackEntity>(entity));
            healthpack->setPos((entity->getXPos())*TILE_SIZE, (entity->getYPos())*TILE_SIZE);
            scene->addItem(healthpack);
        } else if (entity->getType() == EntityType::ENEMY) {
            auto *enemy = new EnemyGraphicsItem(qSharedPointerCast<EnemyEntity>(entity));
            enemy->setPos((entity->getXPos())*TILE_SIZE, (entity->getYPos())*TILE_SIZE);
            scene->addItem(enemy);
            if (qSharedPointerCast<EnemyEntity>(entity)->getState() == EnemyBehaviour::ATTACKED_E) {
                auto *damage = new DamageGraphicsItem();
                damage->setPos((entity->getXPos())*TILE_SIZE, (entity->getYPos())*TILE_SIZE);
                scene->addItem(damage);
            }
        } else if (entity->getType() == EntityType::P_ENEMY) {
            auto *enemy = new PEnemyGraphicsItem(qSharedPointerCast<EnemyEntity>(entity));
            enemy->setPos((entity->getXPos())*TILE_SIZE, (entity->getYPos())*TILE_SIZE);
            scene->addItem(enemy);
            if (qSharedPointerCast<EnemyEntity>(entity)->getState() == EnemyBehaviour::ATTACKED_E) {
                auto *damage = new DamageGraphicsItem();
                damage->setPos((entity->getXPos())*TILE_SIZE, (entity->getYPos())*TILE_SIZE);
                scene->addItem(damage);
            }
        } else if (entity->getType() == EntityType::X_ENEMY) {
            auto *enemy = new XEnemyGraphicsItem(qSharedPointerCast<EnemyEntity>(entity));
            enemy->setPos((entity->getXPos())*TILE_SIZE, (entity->getYPos())*TILE_SIZE);
            scene->addItem(enemy);
            if (qSharedPointerCast<EnemyEntity>(entity)->getState() == EnemyBehaviour::ATTACKED_E) {
                auto *damage = new DamageGraphicsItem();
                damage->setPos((entity->getXPos())*TILE_SIZE, (entity->getYPos())*TILE_SIZE);
                scene->addItem(damage);
            }
        } else if (entity->getType() == EntityType::PORTAL) {
            auto *portal = new PortalGraphicsItem();
            portal->setPos((entity->getXPos())*TILE_SIZE, (entity->getYPos())*TILE_SIZE);
            scene->addItem(portal);
        }
    }
    player->setPosition(gameWorld->getPlayer()->getX()*TILE_SIZE,
                        gameWorld->getPlayer()->getY()*TILE_SIZE);
    scene->addItem(player);
    scene->setPlayerView(player);

    if (scene->isShowingHighlights()) {

        int currentX = scene->getXStart();
        int currentY = scene->getYStart();

        QRectF tileRect(currentX * TILE_SIZE, currentY * TILE_SIZE, TILE_SIZE, TILE_SIZE);
        auto highlight = new QGraphicsRectItem(tileRect);
        highlight->setBrush(QColor(255, 0, 255, 100));
        highlight->setPen(QPen(Qt::magenta, 2));
        scene->addItem(highlight);

        auto path = scene->getPath();

        while (!path.empty()) {
            Direction dir = path.front();

            switch(dir) {
            case Direction::UP:
                currentY--;
                break;
            case Direction::RIGHT:
                currentX++;
                break;
            case Direction::DOWN:
                currentY++;
                break;
            case Direction::LEFT:
                currentX--;
                break;
            }
            QRectF tileRect(currentX * TILE_SIZE, currentY * TILE_SIZE, TILE_SIZE, TILE_SIZE);
            auto highlight = new QGraphicsRectItem(tileRect);
            highlight->setBrush(QColor(255, 0, 255, 100));
            highlight->setPen(QPen(Qt::magenta, 2));
            scene->addItem(highlight);

            path.pop();
        }
    }
}
