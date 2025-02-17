#include "entity.h"

Entity::Entity(int x, int y): x{x}, y{y} {}


bool Entity::isPlayerNearby(QSharedPointer<Player> player){
    int dx = abs(player->getX() - x);
    int dy = abs(player->getY() - y);
    return (dx <= 1 && dy <= 1 && (dx + dy) > 0);
}

void Entity::toBinary(QDataStream& o) const {
    // o << static_cast<int>(getType());
    o << x;
    o << y;
}

void Entity::fromBinary(QDataStream& i){
    // int typeInt;
    // i >> typeInt;
    i >> x;
    i >> y;

    // getType =  static_cast<EntityType>(typeInt);
}
