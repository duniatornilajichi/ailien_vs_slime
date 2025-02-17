#ifndef PENEMYENTITY_H
#define PENEMYENTITY_H

#include "enemyentity.h"

class PEnemyEntity: public EnemyEntity
{
public:
    PEnemyEntity() = default;
    PEnemyEntity(int x, int y):EnemyEntity(x,y), spreadPoison{false}{ };

    void toBinary(QDataStream& o) const override {
        EnemyEntity::toBinary(o);
        o << spreadPoison;
        o << count;
    }

    void fromBinary(QDataStream& i) override {
        EnemyEntity::fromBinary(i);
        i >> spreadPoison;
        i >> count;
    }

    void refresh(QSharedPointer<Player> player,
                 QList<QList<QSharedPointer<Block>>>& blockMatrix,
                 QList<QSharedPointer<Entity>>& entityList) override;
    void interactBy(QSharedPointer<Player> player,
                    QList<QSharedPointer<Block>> affectedBlocks,
                    QList<QSharedPointer<Entity>>& entityList) override;
    inline EntityType getType() const override {return EntityType::P_ENEMY; }

private:
    bool spreadPoison{false};
    int count{0};
};

#endif // PENEMYENTITY_H
