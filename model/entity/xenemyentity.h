#ifndef XENEMYENTITY_H
#define XENEMYENTITY_H
#include "enemyentity.h"
class XEnemyEntity: public EnemyEntity, public  QEnableSharedFromThis<Entity>
{
public:
    XEnemyEntity() = default;
    XEnemyEntity(int x, int y): EnemyEntity(x, y) {};

    void refresh(QSharedPointer<Player> player,
                 QList<QList<QSharedPointer<Block>>>& blockMatrix,
                 QList<QSharedPointer<Entity>>& entityList) override;
    void interactBy(QSharedPointer<Player> player,
                    QList<QSharedPointer<Block>> affectedBlocks,
                    QList<QSharedPointer<Entity>>& entityList) override;
    inline EntityType getType() const override {return EntityType::X_ENEMY; }

};

#endif // XENEMYENTITY_H
