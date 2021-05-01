#include "Tower.h"


Tower::Tower(tImages& Texture, vectorF Pos, unsigned int Price) :
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

SingleTower::SingleTower(tImages& Texture, vectorF pos) :
    Tower(
        Texture,
        pos,
        singleTowerPrice
    ) {
}

MultiTower::MultiTower(tImages& Texture, vectorF pos) :
    Tower(
        Texture,
        pos,
        multiTowerPrice
    ) {
    this->shotCount = multiTowerShotCount;
    this->setReload(-0.5);
}

FreezingTower::FreezingTower(tImages& Texture, vectorF pos) :
    Tower(
        Texture,
        pos,
        freezingTowerPrice
    ) {
}

OnePunchTower::OnePunchTower(tImages& Texture, vectorF pos) :
    Tower(
        Texture,
        pos,
        onePunchTowerPrice
    ) {
}

// Preparing tower animation for update
void Tower::Update(float deltaTime) {
    Animation.Update(0, deltaTime, faceRight);
    Body.setTextureArea(Animation.uvRect);
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
    creep.ballsFollow.push_back(fireball);
    this->Timer = this->getReload();
}

void MultiTower::Fire(Creep& creep) {
    FireBall fireball(this->getPosition());
    creep.ballsFollow.push_back(fireball);
    this->Timer = this->getReload();
}

void FreezingTower::Fire(Creep& creep) {
    SnowBall snowball(this->getPosition());
    creep.ballsFollow.push_back(snowball);
    this->Timer = this->getReload();
}

void OnePunchTower::Fire(Creep& creep) {
    DesolBall desolball(this->getPosition());
    creep.ballsFollow.push_back(desolball);
    this->Timer = this->getReload();
}

userCircleShape Tower::getArea() {
    return rangeArea;
}


float Tower::getReload() {
    return Reload;
}
