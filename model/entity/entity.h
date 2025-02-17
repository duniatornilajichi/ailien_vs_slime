#ifndef ENTITY_H
#define ENTITY_H

#include "../player.h"
#include <QSharedPointer>

enum class EntityType{
    ENEMY,
    P_ENEMY,
    X_ENEMY,
    HEALTHPACK,
    P_TERRAIN,
    PORTAL,
    ENERGYPACK
};

class Block;
class Entity
{
public:
    Entity() = default;

    virtual ~Entity() = default;
    Entity(int x, int y);

    virtual void refresh(QSharedPointer<Player> player,
                         QList<QList<QSharedPointer<Block>>>& blockMatrix,
                         QList<QSharedPointer<Entity>>& entityList) = 0;
    virtual void interactBy(QSharedPointer<Player> player,
                            QList<QSharedPointer<Block>> affectedBlocks,
                            QList<QSharedPointer<Entity>>& entityList) = 0;
    virtual EntityType getType() const = 0;
    inline int getXPos() const { return x; };
    inline int getYPos() const { return y; };

    virtual void toBinary(QDataStream& out) const;
    virtual void fromBinary(QDataStream& in);
protected:
    bool isPlayerNearby(QSharedPointer<Player> player);
    int x;
    int y;
};

#endif // ENTITY_H
