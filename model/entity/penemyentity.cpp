#include "penemyentity.h"
#include "model/block.h"
#include "poisonedterrainentity.h"

void PEnemyEntity::refresh(QSharedPointer<Player> player,
                           QList<QList<QSharedPointer<Block>>>& blockMatrix,
                           QList<QSharedPointer<Entity>>& entityList){
    EnemyEntity::refresh(player, blockMatrix, entityList);
    if(spreadPoison && count >= 0 && count < 5){
        int max_y = blockMatrix.length();
        int max_x;
        if(max_y>0){ max_x = blockMatrix[0].length();}
        else{ max_x=0;}
        for(int i = -count; i<= count; i++){
            for(int j = -count; j<=count; j++){
                int newX = x+j;
                int newY = y+i;

                if ( newX >= 0 && newX < max_x && newY >= 0 && newY < max_y) {
                    auto entityBlock = blockMatrix[newY][newX];
                    if (!entityBlock->getEntity()) {
                        QSharedPointer<Entity> poison = QSharedPointer<PoisonedTerrainEntity>::create(newX, newY, strength/10);
                        entityList.push_back(poison);
                        auto entityBlock = blockMatrix[poison->getYPos()][poison->getXPos()];
                        entityBlock->setEntity(poison);
                        entityBlock->setSteppable(true);
                    }
                }
            }
        }
        count++;
    }
}

void PEnemyEntity::interactBy(QSharedPointer<Player> player,
                              QList<QSharedPointer<Block>> affectedBlocks,
                              QList<QSharedPointer<Entity>>& entityList){
    EnemyEntity::interactBy(player,affectedBlocks,entityList);
    if (!isAlive()) return;
    if(!spreadPoison){
        spreadPoison = true;
    }
}

