#include "poisonedterrainentity.h"

void PoisonedTerrainEntity::refresh(QSharedPointer<Player> player,
                                    QList<QList<QSharedPointer<Block>>>& blockMatrix,
                                    QList<QSharedPointer<Entity>>& entityList){
    if(player->getX()== x && player->getY()==y){
       player->changeHealthBy(-strength);
    }
}
