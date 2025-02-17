#include "xenemyentity.h"
#include "model/gameworld.h"
#include <QPointer>


void XEnemyEntity::refresh(QSharedPointer<Player> player,
                           QList<QList<QSharedPointer<Block>>>& blockMatrix,
                           QList<QSharedPointer<Entity>>& entityList){
    if (!isAlive()) return;

    int dx = player->getX()-x;
    int dy = player->getY()-y;

    if(std::abs(dx)<=1){
        dx = 0;
    }else{
        dx = dx/(std::abs(dx));
    }
    if (std::abs(dy)<= 1){
        dy = 0;
    }else{
        dy = dy/(std::abs(dy));
    }
    auto block = blockMatrix[y+dy][x+dx]; //block is null
    auto oldBlock = blockMatrix[y][x];
    if(block){
        if(block->isSteppable() &&  !(dx==0 && dy==0)){
            x+= dx;
            y+= dy;
            block->setEntity(QSharedPointer<Entity>(sharedFromThis()));
            block->setSteppable(false);
            oldBlock->removeEntity();
        }
    }
    EnemyEntity::refresh(player, blockMatrix, entityList);
}


void XEnemyEntity::interactBy(QSharedPointer<Player> player,
                              QList<QSharedPointer<Block>> affectedBlocks,
                              QList<QSharedPointer<Entity>>& entityList){
    EnemyEntity::interactBy(player,affectedBlocks,entityList);
}
