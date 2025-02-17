#ifndef ENERGYPACKENTITY_H
#define ENERGYPACKENTITY_H
#include "entity.h"

class EnergyPackEntity: public Entity
{
public:
    EnergyPackEntity() = default;
    EnergyPackEntity(int x, int y);
    EnergyPackEntity(int x, int y, float strength);

    void refresh(QSharedPointer<Player> player,
                 QList<QList<QSharedPointer<Block>>>& blockMatrix,
                 QList<QSharedPointer<Entity>>& entityList) override {}
    void interactBy(QSharedPointer<Player> player,
                    QList<QSharedPointer<Block>> affectedBlocks,
                    QList<QSharedPointer<Entity>>& entityList) override;
    inline EntityType getType() const override {return EntityType::ENERGYPACK; }

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
    float strength{15.0};
    bool full{true};

};

#endif // ENERGYPACKENTITY_H
