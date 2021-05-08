#include "Additional.h"

userImages tFireball, tSnowball, tDesolball;


Ball::Ball(Vector<float> towerPos, int n) {

    tFireball.loadTexture("images/Fireball.png");
    tSnowball.loadTexture("images/Snowball.png");
    tDesolball.loadTexture("images/Snowball.png");

    if (n == 1)
        this->Body.setTexture(&tFireball);
    if (n == 2)
        this->Body.setTexture(&tSnowball);
    if (n == 3)
        this->Body.setTexture(&tDesolball);
    this->Body.setRad(defaultRadius);
    this->Body.setPos(towerPos.x + towerSize.x / 2, towerPos.y + towerSize.y / 2);

    this->Speed = defaultBallSpeed;
}

Vector<float> Ball::getPosition() {
    Vector<float> pos;
    pos.x = this->Body.getPos().x;
    pos.y = this->Body.getPos().y;
    return pos;
}


userCircleShape Ball::getBody() {
    return this->Body;
}

float Ball::getDamage()
{
    return Damage;
}

void Ball::setDamage(float Damage) {
    this->Damage = Damage;
}

void Ball::setDesolation(float Desol) {
    this->Desolation = Desol;
}

float Ball::getDesolation() {
    return this->Desolation;
}

void Ball::setSlow(float Slow) {
    this->Slow = Slow;
}

float Ball::getSlow() {
    return this->Slow;
}



FireBall::FireBall(Vector<float> towerPos) :
    Ball(
        towerPos,
        1
    ) {
    this->setDamage(fireBallDamage);
    this->setSlow(0);
    this->setDesolation(0);
}

SnowBall::SnowBall(Vector<float> towerPos) :
    Ball(
        towerPos,
        2
    ) {
    this->setDamage(snowBallDamage);
    this->setSlow(slowSnowBall);
    this->setDesolation(0);
}

DesolBall::DesolBall(Vector<float> towerPos) :
    Ball(
        towerPos,
        3
    ) {
    this->setDamage(desolBallDamage);
    this->setSlow(0);
    this->setDesolation(desolDesolBall);
}



// Animation update

void Ball::Update(float xCreep, float yCreep, float deltaTime) {
    Vector<float> movement = { 0.0f, 0.0f };
    float deltaX = xCreep - (this->Body.getPos().x + this->Body.gGB().width / 2);
    float deltaY = yCreep - (this->Body.getPos().y + this->Body.gGB().height / 2);
    float Hyp = sqrt(deltaX * deltaX + deltaY * deltaY);

    movement.x = Speed * deltaTime * deltaX / Hyp;
    movement.y = Speed * deltaTime * deltaY / Hyp;

    this->Body.moveObj(movement.x, movement.y);
}