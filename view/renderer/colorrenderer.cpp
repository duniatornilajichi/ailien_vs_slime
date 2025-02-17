#include "colorrenderer.h"
#include "view/graphicsItem/damagegraphicsitem.h"
#include "view/graphicsItem/enemygraphicsitem.h"
#include "view/graphicsItem/energypackgraphicsitem.h"
#include "view/graphicsItem/penemygraphicsitem.h"
#include "view/graphicsItem/portalgraphicsitem.h"
#include "view/graphicsItem/pterraingraphicsitem.h"
#include "view/graphicsItem/tilegraphicsitem.h"
#include "view/graphicsItem/healthpackgraphicsitem.h"
#include "view/graphicsItem/xenemygraphicsitem.h"
#include <cmath>

void ColorRenderer::populateScene(GameScene *scene, QSharedPointer<GameWorld> gameWorld) {
    const int TILE_SIZE = 40;
    auto blocks = gameWorld->getMatrixBlocks();
    for (int i = 0; i < blocks.size(); i++) {
        for (int j = 0; j < blocks.at(i).size(); j++) {
            TileGraphicsItem *tile = new TileGraphicsItem(TILE_SIZE);
            tile->setPos(j * TILE_SIZE, i * TILE_SIZE);
            tile->setTileColor(pixelValueToHSV(1-blocks.at(i).at(j)->getValue()));
            scene->addItem(tile);
        }
    }
    auto v_player = new PlayerGraphicsItem(gameWorld->getPlayer());
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
    v_player->setPosition(gameWorld->getPlayer()->getX()*TILE_SIZE,
                        gameWorld->getPlayer()->getY()*TILE_SIZE);
    scene->addItem(v_player);
    scene->setPlayerView(v_player);


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



QColor ColorRenderer::pixelValueToHSV(float pixelValue) {

    if (std::isinf(pixelValue)) { // take care of wall pixels
        pixelValue = 1.0f;
    }

    //float clampedLogValue = std::log1p(pixelValue) / std::log1p(1.0f);
    float clampedPixelValue = std::max(0.0f, std::min(pixelValue, 1.0f));

    int hue = static_cast<int>(clampedPixelValue * 240);
    int saturation = 255;
    int value = 190 - static_cast<int>(clampedPixelValue * 50);

    QColor color;
    color.setHsv(hue, saturation, value);
    return color;
}
