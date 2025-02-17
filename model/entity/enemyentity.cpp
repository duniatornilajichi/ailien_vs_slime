#include "enemyentity.h"

EnemyEntity::EnemyEntity(int x, int y, float strength) :Entity(x,y), strength{strength}, alive{true} {}
EnemyEntity::EnemyEntity(int x, int y) :EnemyEntity(x,y, ENEMY_STRENGTH) {}

void EnemyEntity::refresh(QSharedPointer<Player> player,
                          QList<QList<QSharedPointer<Block>>>& blockMatrix,
                          QList<QSharedPointer<Entity>>& entityList){
    if(isPlayerNearby(player) && isAlive()){
        currentState = EnemyBehaviour::ATTACK_E;
        player->changeHealthBy(-strength);
    } else {
        currentState = EnemyBehaviour::IDLE_E;
    }
}

void EnemyEntity::interactBy(QSharedPointer<Player> player,
                             QList<QSharedPointer<Block>> affectedBlocks,
                             QList<QSharedPointer<Entity>>& entityList){
    if (!isAlive()) return;
    if (health > 0) {
        currentState = EnemyBehaviour::ATTACKED_E;
        health -= player->getEnergy()/4; // TODO: Disscuss attack strengths
    } else {
        currentState = EnemyBehaviour::KILLED_E;
        alive = false;
    }
}



