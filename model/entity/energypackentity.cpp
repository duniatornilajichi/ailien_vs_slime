#include "energypackentity.h"

EnergyPackEntity::EnergyPackEntity(int x, int y, float strength) :Entity(x, y), strength{strength}, full{true}{}
EnergyPackEntity::EnergyPackEntity(int x, int y) :EnergyPackEntity(x, y, 15.0){}

void EnergyPackEntity::interactBy(QSharedPointer<Player> player,
                                  QList<QSharedPointer<Block>> affectedBlocks,
                                  QList<QSharedPointer<Entity>>& entityList){
    if(full){
        player->changeEnergyBy(strength);
        full = false;
    }
}
