#include "../include/Tower.h"


Tower::Tower(userImages& Texture, Vector<float> Pos, unsigned int Price) :
    Unit(
        Texture,
        towerImageCount,
        towerSize.x,
        towerSize.y) {
    this->Price = Price;
    this->Reload = towerReloadTime;
    this->rangeArea.setRadius(towerRadius);
    this->Body.setPos(Pos.x, Pos.y);
}

SingleTower::SingleTower(userImages& Texture, Vector<float> pos) :
    Tower(
        Texture,
        pos,
        singleTowerPrice
    ) {
}

MultiTower::MultiTower(userImages& Texture, Vector<float> pos) :
    Tower(
        Texture,
        pos,
        multiTowerPrice
    ) {
    this->shotCount = multiTowerShotCount;
    this->setReload(-0.5);
}

FreezingTower::FreezingTower(userImages& Texture, Vector<float> pos) :
    Tower(
        Texture,
        pos,
        freezingTowerPrice
    ) {
}

OnePunchTower::OnePunchTower(userImages& Texture, Vector<float> pos) :
    Tower(
        Texture,
        pos,
        onePunchTowerPrice
    ) {
}

// Preparing tower animation for update
void Tower::Update(float deltaTime) {
    animation.Update(0, deltaTime, faceRight);
    Body.setTextureArea(animation.uvRect);
}

int Tower::getPrice() {
    return Price;
}

void Tower::setReload(float time) {
    this->Reload += time;
}

void Tower::Fire(Creep& creep) {}


// Redefinition of method fire()

void SingleTower::Fire(Creep& creep) {
    FireBall fireball(this->getPosition());
    creep.addBall(fireball);
    this->Timer = this->getReload();
}

void MultiTower::Fire(Creep& creep) {
    FireBall fireball(this->getPosition());
    creep.addBall(fireball);
    this->Timer = this->getReload();
}

void FreezingTower::Fire(Creep& creep) {
    SnowBall snowball(this->getPosition());
    creep.addBall(snowball);
    this->Timer = this->getReload();
}

void OnePunchTower::Fire(Creep& creep) {
    DesolBall desolball(this->getPosition());
    creep.addBall(desolball);
    this->Timer = this->getReload();
}

userCircleShape Tower::getArea() {
    return rangeArea;
}


float Tower::getReload() {
    return Reload;
}
