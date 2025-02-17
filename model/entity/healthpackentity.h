#ifndef HEALTHPACKENTITY_H
#define HEALTHPACKENTITY_H
#include "entity.h"

class HealthpackEntity: public Entity
{
public:
    HealthpackEntity() = default;
    HealthpackEntity(int x, int y);
    HealthpackEntity(int x, int y, float strength);

    void refresh(QSharedPointer<Player> player,
                 QList<QList<QSharedPointer<Block>>>& blockMatrix,
                 QList<QSharedPointer<Entity>>& entityList) override {}
    void interactBy(QSharedPointer<Player> player,
                    QList<QSharedPointer<Block>> affectedBlocks,
                    QList<QSharedPointer<Entity>>& entityList) override;
    inline EntityType getType() const override {return EntityType::HEALTHPACK; }

    inline float getStrength() const { return strength; };
    inline bool isFull() const { return full; };

    void toBinary(QDataStream& o) const override {
        Entity::toBinary(o);
        o << strength;
        o << full;
    }

    void fromBinary(QDataStream& i) override {
        Entity::fromBinary(i);
        i >> strength;
        i >> full;
    }

private:
    float strength{20.0};
    bool full{true};
};

#endif // HEALTHPACKENTITY_H
