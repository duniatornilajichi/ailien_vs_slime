#include "gameworld.h"
#include "model/entity/healthpackentity.h"
#include "model/pathnode.h"
#include "model/entity/penemyentity.h"
#include "qdebug.h"
#include <QSharedPointer>
#include "world.h"
#include "model/entity/xenemyentity.h"
#include "model/entity/portalentity.h"
#include "model/entity/energypackentity.h"

GameWorld::GameWorld(QString filename,
                     Level level,
                     float pRatio,
                     float xRatio){

    LevelInfo levelInfo = LevelInfo::getLevelInfo(level);
    currentLevel = level;
    int nEnemies = levelInfo.nEnemies;
    int nHealthpacks = levelInfo.nHealthpacks;
    std::unique_ptr<World> baseWorld = std::make_unique<World>();
    baseWorld->createWorld(filename, nEnemies, nHealthpacks, pRatio);
    int nrows = baseWorld->getRows()+2;
    int ncols = baseWorld->getCols()+2;
    matrixBlocks.resize(nrows);
    for (int i = 0; i < nrows; i++) {
        matrixBlocks[i].resize(ncols);
    }
    const auto tiles = baseWorld->getTiles();
    for (int i = 0; i < nrows; i++) {
        for (int j = 0; j < ncols; j++) {
            if(i==0||i==(nrows-1) || j==0||j==(ncols-1)){   //This adds a wall around the world
                matrixBlocks[i][j] = QSharedPointer<Block>::create(BlockType::WALL);
            }
            else{   //This adds the world inside thw walls
                int k = (i-1)*(nrows-2)+(j-1);
                matrixBlocks[i][j] = QSharedPointer<Block>::create(tiles[k]->getValue());
            }
        }

    }

    if(level> Level::L1){
        QSharedPointer<Entity> newPortal = QSharedPointer<PortalEntity>::create(1, 1, level, false); //auto newPortal = QSharedPointer<PortalEntity>(new PortalEntity(ncols-1, nrows-1));
        addEntity(newPortal);
        portalBack = qSharedPointerCast<PortalEntity>(newPortal);
    }

    QSharedPointer<Entity> newPortal = QSharedPointer<PortalEntity>::create(ncols-2, nrows-2, level, true); //auto newPortal = QSharedPointer<PortalEntity>(new PortalEntity(ncols-1, nrows-1));
    addEntity(newPortal);
    portalFoward = qSharedPointerCast<PortalEntity>(newPortal);

    player = QSharedPointer<Player>::create(1, 1);
    const auto enemies = baseWorld->getEnemies();
    const auto healthpacks = baseWorld->getHealthPacks();

    listEntities.reserve(enemies.size()+healthpacks.size());
    for (auto& enemy:enemies){
        int x = enemy->getXPos();
        int y = enemy->getYPos();
        if (dynamic_cast<PEnemy*>(enemy.get())) {
            QSharedPointer<Entity> penemyEntity = QSharedPointer<PEnemyEntity>::create(x+1,y+1);
            addEntity(penemyEntity);
        } else {
            QSharedPointer<Entity> enemyEntity = QSharedPointer<EnemyEntity>::create(x+1,y+1);
            addEntity(enemyEntity);
        }
    }
    for (int i = 0, j = 0; j < listEntities.length()*xRatio; i++) {
        auto enemy = listEntities[i];
        if (enemy->getType() == EntityType::ENEMY) {
            QSharedPointer<Entity> xEnemy = QSharedPointer<XEnemyEntity>::create(enemy->getXPos(),enemy->getYPos());
            listEntities[i] = xEnemy;
            matrixBlocks[enemy->getYPos()][enemy->getXPos()]->setEntity(xEnemy);
            j++;
        }
    }
    for(int i = 0; i < (int)healthpacks.size()/2; i++) {
        int x = healthpacks[i]->getXPos();
        int y = healthpacks[i]->getYPos();
        QSharedPointer<Entity> healthpEntity = QSharedPointer<HealthpackEntity>::create(x+1,y+1);
        addEntity(healthpEntity);
    }
    for(int i = (int)healthpacks.size()/2; i < (int)healthpacks.size(); i++) {
        int x = healthpacks[i]->getXPos();
        int y = healthpacks[i]->getYPos();
        QSharedPointer<Entity> energypEntity = QSharedPointer<EnergyPackEntity>::create(x+1,y+1);
        addEntity(energypEntity);
    }
}

void GameWorld::movePlayer(Direction direction)
{
    int dx = 0;
    int dy = 0;
    switch(direction){
    case Direction::UP:
        dy--;
        break;
    case Direction::DOWN:
        dy++;
        break;
    case Direction::LEFT:
        dx--;
        break;
    case Direction::RIGHT:
        dx++;
        break;
    }
    int newX = player->getX()+dx;
    int newY = player->getY()+dy;
    if(isInBounds(newX, newY)){
        auto newBlock = matrixBlocks[newY][newX];
        if(newBlock->isSteppable()){
            player->setCurrentState(PlayerBehaviour::MOVE);
            player->setX(newX);
            player->setY(newY);
            player->changeEnergyBy(-(newBlock->getEnergy()));
            emit updateWorld(sharedFromThis());
        }
    }
}

void GameWorld::interactPlayer(){
    int x = player->getX();
    int y = player->getY();
    for(auto &block : getExpandingBlocks(x,y, 1)){
        auto entity = block->getEntity();
        if(entity){
            entity->interactBy(player, getExpandingBlocks(x,y, 1), listEntities);
            if (entity->getType() == EntityType::HEALTHPACK)
                player->setCurrentState(PlayerBehaviour::ENERGISING);
        }
    }
    emit updateWorld(sharedFromThis());
}

void GameWorld::refresh(){
    player->setCurrentState(PlayerBehaviour::IDLE);
    for(auto &entity: listEntities){
        entity->refresh(player, matrixBlocks, listEntities);
    }
    emit updateWorld(sharedFromThis());
}

QList<QSharedPointer<Block>> GameWorld::getExpandingBlocks(int x, int y, int layer) const {
    QList<QSharedPointer<Block>> nearBlocks;
    nearBlocks.reserve((2*layer-1)*(2*layer-1));
    for(int i = -layer; i<= layer; i++){
        for(int j = -layer; j<=layer; j++){
            if(std::abs(i) == layer || std::abs(j)==layer){
                int newX = x+j;
                int newY = y+i;
                if(isInBounds(newX, newY)){
                    nearBlocks.push_back(matrixBlocks[newY][newX]);
                }
            }
        }
    }
    return nearBlocks;
}

QSharedPointer<Block> GameWorld::getBlock(int x, int y) const {
    if(isInBounds(x,y)){
        return matrixBlocks[y][x];
    }
    return nullptr;
}

void GameWorld::addEntity(QSharedPointer<Entity> entity){
    if (!isInBounds(entity->getXPos(), entity->getYPos()) ||
        matrixBlocks[entity->getYPos()][entity->getXPos()]->getEntity() ||
        matrixBlocks[entity->getYPos()][entity->getXPos()]->getType() == BlockType::WALL)
        return;
    listEntities.push_back(entity);
    auto entityBlock = matrixBlocks[entity->getYPos()][entity->getXPos()];
    entityBlock->setEntity(entity);
    entityBlock->setSteppable(false);
}


bool GameWorld::isInBounds(int x, int y) const {
    int max_y = matrixBlocks.length();
    int max_x;
    if(max_y>0){ max_x = matrixBlocks[0].length();}
    else{ max_x=0;}
    return x >= 0 && x < max_x && y >= 0 && y < max_y;
}

void GameWorld::toBinary(QDataStream& o) const {
    o << static_cast<int>(currentLevel);
    o << matrixBlocks.size();
    o << matrixBlocks[0].size();
    for (const auto& row : matrixBlocks) {
        for (const auto& block : row) {
            block->toBinary(o);
        }
    }

    o << listEntities.size();
    for (const auto& entity : listEntities) {
        entity->toBinary(o);
    }
}

void GameWorld::fromBinary(QDataStream& in) {
    int levelInt;
    in >> levelInt;
    currentLevel = static_cast<Level>(levelInt);

    int numRows, numCols;
    in >> numRows >> numCols;

    matrixBlocks.clear();
    for (int i = 0; i < numRows; ++i) {
        QList<QSharedPointer<Block>> row;
        for (int j = 0; j < numCols; ++j) {
            QSharedPointer<Block> block = QSharedPointer<Block>::create();
            block->fromBinary(in);
            row.append(block);
        }
        matrixBlocks.append(row);
    }

    int numEntities;
    in >> numEntities;
    listEntities.clear();
    for (int i = 0; i < numEntities; ++i) {
        QSharedPointer<Entity> entity = nullptr;
        entity->fromBinary(in);
        listEntities.append(entity);
    }
}

void GameWorld::findPath() {
    auto blocks = getMatrixBlocks();

    pathFinder = QSharedPointer<PathFinderAdapter>::create(blocks);

    int playerX = player->getX();
    int playerY = player->getY();
    int targetX = getPortalFoward()->getXPos();
    int targetY = getPortalFoward()->getYPos();

    // Validate coordinates
    int width = blocks[0].size();
    int height = blocks.size();
    if (playerX < 0 || playerX >= width || playerY < 0 || playerY >= height ||
        targetX < 0 || targetX >= width || targetY < 0 || targetY >= height) {
        qDebug() << "Coordinates out of bounds";
        return;
    }

    int startIndex = playerY * width + playerX;
    int targetIndex = targetY * width + targetX;

    // Validate node grid
    auto nodeGrid = pathFinder->getNodeGrid();
    if (nodeGrid.empty() || startIndex >= (int)nodeGrid.size() || targetIndex >= (int)nodeGrid.size()) {
        qDebug() << "Invalid node grid or indices";
        return;
    }

    try {
        QSharedPointer<PathNode> startNode = QSharedPointer<PathNode>::create(
            nodeGrid[startIndex]
            );

        QSharedPointer<PathNode> targetNode = QSharedPointer<PathNode>::create(
            nodeGrid[targetIndex]
            );

        std::vector<int> path = pathFinder->findPath(startNode, targetNode);
        emit pathFound(path);
        qDebug() << "emit path Found";
    } catch (const std::exception& e) {
        qDebug() << "Exception during path finding:" << e.what();
    }
}

