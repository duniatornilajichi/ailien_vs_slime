#include "player.h"
#include <QTimer>
#include <QDebug>
Player::Player(QObject *parent): QObject(parent) {
    x = 0;
    y = 0;
    health = HEALTH_LIM;
    energy = ENERGY_LIM;
    isAlive = true;

}

Player::Player(int x, int y, float health, float energy):x{x}, y{y}, health{health}, energy{energy} {}
Player::Player(int x, int y):x{x}, y{y}{}

void Player::setX(int newX){
    x = newX;
}

void Player::setY(int newY){
    y =newY;
}

void Player::changeEnergyBy(float change){
    energy += change;
    if(energy > ENERGY_LIM){ energy = ENERGY_LIM;}
    else if(energy <= 0.0){
        //TO DO: send signal die to controller
        energy = 0.0;
        currentState = PlayerBehaviour::DIE;
        emit changePlayerState(PlayerBehaviour::DIE);
        emit died();
    }
    if (change > 0.0) {
        currentState = PlayerBehaviour::ENERGISING;
    }
}
void Player::changeHealthBy(float change){
    health += change;
    if (change < 0)
        currentState = PlayerBehaviour::ATTACKED;

    if(health > HEALTH_LIM)
        health = HEALTH_LIM;
    else if(health <= 0.0){
        currentState = PlayerBehaviour::DIE;
        health = 0.0;
        emit died();
    }
}

void Player::toBinary(QDataStream& o)const{
    o << x;
    o << y;
    o << health;
    o << energy;
    o << isAlive;
    o << static_cast<int>(currentState);
}

void Player::fromBinary(QDataStream& i){
    i >> x;
    i >> y;
    i >> health;
    i >> energy;
    i >> isAlive;
    int stateInt;
    i >> stateInt;
    currentState = static_cast<PlayerBehaviour>(stateInt);
}
