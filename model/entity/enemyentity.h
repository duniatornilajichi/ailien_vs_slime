#ifndef ENEMYENTITY_H
#define ENEMYENTITY_H
#include "entity.h"

class EnemyEntity: public Entity
{
public:
    EnemyEntity() = default;
    EnemyEntity(int x, int y);
    EnemyEntity(int x, int y, float strength);

    inline virtual EntityType getType() const override { return EntityType::ENEMY; };
    virtual void refresh(QSharedPointer<Player> player,
                         QList<QList<QSharedPointer<Block>>>& blockMatrix,
                         QList<QSharedPointer<Entity>>& entityList) override;
    virtual void interactBy(QSharedPointer<Player> player,
                            QList<QSharedPointer<Block>> affectedBlocks,
                            QList<QSharedPointer<Entity>>& entityList) override;
    inline float getStrength() const { return strength; };
    inline bool isAlive() const { return alive; };
    inline EnemyBehaviour getState() const { return currentState; };

    void toBinary(QDataStream& o) const override {
        Entity::toBinary(o);
        o << strength;
        o << health;
        o << alive;
    }

    void fromBinary(QDataStream& i) override {
        Entity::fromBinary(i);
        i >> strength;
        i >> health;
        i >> alive;
    }
    static constexpr float ENEMY_STRENGTH = 10;
    static constexpr float ENEMY_HEALTH = 100;

protected:
    float strength{ENEMY_STRENGTH};
    float health{ENEMY_HEALTH};
    bool alive{true};
    EnemyBehaviour currentState{EnemyBehaviour::IDLE_E};
};

#endif // ENEMYENTITY_H
