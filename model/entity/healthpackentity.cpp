#include "healthpackentity.h"

HealthpackEntity::HealthpackEntity(int x, int y, float strength) :Entity(x, y), strength{strength}, full{true} {}
HealthpackEntity::HealthpackEntity(int x, int y):HealthpackEntity(x, y, 10.0){}

void HealthpackEntity::interactBy(QSharedPointer<Player> player,
                                  QList<QSharedPointer<Block>> affectedBlocks,
                                  QList<QSharedPointer<Entity>>& entityList){
    if(full){
        player->changeHealthBy(strength);
        full = false;
    }
}
