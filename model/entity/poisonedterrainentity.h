#ifndef POISONEDTERRAINENTITY_H
#define POISONEDTERRAINENTITY_H
#include "enemyentity.h"

class PoisonedTerrainEntity: public EnemyEntity
{
public:
    PoisonedTerrainEntity() = default;
    PoisonedTerrainEntity(int x, int y, float strength):EnemyEntity(x,y,strength){};

    void refresh(QSharedPointer<Player> player,
                 QList<QList<QSharedPointer<Block>>>& blockMatrix,
                 QList<QSharedPointer<Entity>>& entityList) override;
    void interactBy(QSharedPointer<Player> player,
                    QList<QSharedPointer<Block>> affectedBlocks,
                    QList<QSharedPointer<Entity>>& entityList) override{};
    inline EntityType getType() const override {return EntityType::P_TERRAIN; }
};

#endif // POISONEDTERRAINENTITY_H
