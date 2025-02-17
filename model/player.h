#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>

#include "behaviour.h"


class Player: public QObject
{
    Q_OBJECT
public:
    explicit Player(QObject *parent = nullptr);
    Player() = default;
    Player(int x, int y);
    Player(int x, int y, float health, float energy);//not sure but we might need it if we want player to start in the middle
    ~Player() = default;

    void setX(int newX);
    void setY(int newY);
    void changeEnergyBy(float change);
    void changeHealthBy(float change);

    inline float getHealth() const { return health; };
    inline float getEnergy() const { return energy; };
    inline int getX() const { return x; };
    inline int getY() const { return y; };

    inline PlayerBehaviour getCurrentState() const { return currentState; };
    inline void setCurrentState(PlayerBehaviour behaviour) { currentState = behaviour; }

    void toBinary(QDataStream& out) const;
    void fromBinary(QDataStream& in);

    inline bool hasDied() const { return !isAlive; }; //checks if player has died

    static constexpr float HEALTH_LIM = 100.0;
    static constexpr float ENERGY_LIM = 100.0;
signals:
    void updateSprite(int index);
    void changePlayerState(PlayerBehaviour newBehaviour);
    void died();

private:
    int x{0};
    int y{0};
    float health{HEALTH_LIM};
    float energy{ENERGY_LIM};
    bool isAlive{true};

    PlayerBehaviour currentState{PlayerBehaviour::IDLE};
};

#endif // PLAYER_H
