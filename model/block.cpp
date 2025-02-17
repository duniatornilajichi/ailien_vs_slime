#include "block.h"
#include "model/entity/energypackentity.h"
#include "model/entity/entity.h"
#include "model/entity/enemyentity.h"
#include "model/entity/healthpackentity.h"
#include "model/entity/penemyentity.h"
#include "model/entity/poisonedterrainentity.h"
#include "model/entity/portalentity.h"
#include "model/entity/xenemyentity.h"

Block::Block(BlockType newtype)
    :steppable{true}, type{newtype}
{
    switch(newtype){
    case BlockType::WALL:
        energy = 100.0;
        steppable = false;
        value = 0.0F;
        break;
    case BlockType::OBSTACLE:
        energy = 2;
        break;
    case BlockType::ROUGH:
        energy = 1;
        break;
    case BlockType::PLAIN:
        energy = 0.2;
        break;
    case BlockType::SMOOTH:
        energy = 0;
        break;
    default:
        energy = 0;
        break;
    }
}

Block::Block(float newValue)
    : Block(
          std::isinf(newValue)
              ? BlockType::WALL
              : (newValue < 0.25F
                     ? BlockType::OBSTACLE
                     : (newValue < 0.5F
                            ? BlockType::ROUGH
                            : (newValue < 0.75F ? BlockType::PLAIN : BlockType::SMOOTH)))) {
    if (!std::isinf(newValue)) {
        value = newValue;
    }
}

void Block::setEntity(QSharedPointer<Entity> newEntity){
    entity = newEntity;
}

void Block::removeEntity(){
    entity = nullptr;
    if(type != BlockType::WALL){
        steppable = true;
    }
}
void Block::setSteppable(bool isStep){
    steppable = isStep;
}

void Block::toBinary(QDataStream& o) const{
    o << steppable;
    o << static_cast<int>(type);
    o << energy;
    o << value;
    if (entity){
        o << true;
        o << static_cast<int>(entity->getType());
        entity->toBinary(o);
    } else {
        o << false;
    }
}

void Block::fromBinary(QDataStream& i){
    i >> steppable;
    int typeInt;
    i >> typeInt;
    type = static_cast<BlockType>(typeInt);
    i >> energy;
    i >> value;

    bool hasEntity;
    i >> hasEntity;
    if (hasEntity) {
        int entityTypeInt;
        i >> entityTypeInt;
        EntityType entityType = static_cast<EntityType>(entityTypeInt);
        switch (entityType) {
        case EntityType::ENEMY:
            entity = QSharedPointer<EnemyEntity>::create();
            break;
        case EntityType::P_ENEMY:
            entity = QSharedPointer<PEnemyEntity>::create();
            break;
        case EntityType::X_ENEMY:
            entity = QSharedPointer<XEnemyEntity>::create();
            break;
        case EntityType::HEALTHPACK:
            entity = QSharedPointer<HealthpackEntity>::create();
            break;
        case EntityType::ENERGYPACK:
            entity = QSharedPointer<EnergyPackEntity>::create();
            break;
        case EntityType::PORTAL:
            entity = QSharedPointer<PortalEntity>::create();
            break;
        case EntityType::P_TERRAIN:
            entity = QSharedPointer<PoisonedTerrainEntity>::create();
            break;
        default:
            entity.clear();
            return;
        }
        entity->fromBinary(i);
    } else {
        entity.clear();
    }
}
