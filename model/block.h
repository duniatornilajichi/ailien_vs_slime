#ifndef BLOCK_H
#define BLOCK_H

#include "BlockType.h"
#include <QSharedPointer>

class Entity;
class Block
{
public:
    Block() = default;
    ~Block() = default;
    Block(BlockType newtype);
    Block(float newValue);

    inline QSharedPointer<Entity> getEntity() const { return entity; };
    void setEntity(QSharedPointer<Entity> newEntity);
    void removeEntity();
    inline BlockType getType() const { return type; };
    inline float getEnergy() const { return energy; };
    inline float getValue() const { return value; };
    inline bool isSteppable() const { return steppable; };
    void setSteppable(bool isStep);
    void toBinary(QDataStream& out) const;
    void fromBinary(QDataStream& in);
private:
    bool steppable{true};
    BlockType type{BlockType::SMOOTH};
    float energy{0.0};
    float value{0.0};
    QSharedPointer<Entity> entity;
};

#endif // BLOCK_H
