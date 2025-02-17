#ifndef BEHAVIOUR_H
#define BEHAVIOUR_H

#include <QObject>

class Behaviour {
    Q_GADGET
public:
    enum Player{
        IDLE,
        MOVE, // add to make code expandable, not really sure what to implement for move DOWN there just yet,
        ENERGISING,
        ATTACKED, // for player
        DIE,
        ATTACK,
        KILLED // for enemy, for expandability
    };
    enum Enemy{
        IDLE_E,
        ATTACK_E,
        ATTACKED_E,
        KILLED_E
    };
    Q_ENUM(Player);
    Q_ENUM(Enemy);

private:
    explicit Behaviour() {}
};

// this creates aliases
using PlayerBehaviour = Behaviour::Player;
using EnemyBehaviour = Behaviour::Enemy;


#endif // BEHAVIOUR_H
