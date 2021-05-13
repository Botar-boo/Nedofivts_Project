#include "Tower.h"


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

void Tower::Fire(std::pair<Creep, std::vector<Ball>>& creep) {}


// Redefinition of method fire()

void SingleTower::Fire(std::pair<Creep, std::vector<Ball>>& creep) {
    FireBall fireball(this->getPosition());
    creep.second.push_back(fireball);
    this->Timer = this->getReload();
}

void MultiTower::Fire(std::pair<Creep, std::vector<Ball>>&creep) {
    FireBall fireball(this->getPosition());
    creep.second.push_back(fireball);
    this->Timer = this->getReload();
}

void FreezingTower::Fire(std::pair<Creep, std::vector<Ball>>& creep) {
    SnowBall snowball(this->getPosition());
    creep.second.push_back(snowball);
    this->Timer = this->getReload();
}

void OnePunchTower::Fire(std::pair<Creep, std::vector<Ball>>& creep) {
    DesolBall desolball(this->getPosition());
    creep.second.push_back(desolball);
    this->Timer = this->getReload();
}

userCircleShape Tower::getArea() {
    return rangeArea;
}


float Tower::getReload() {
    return Reload;
}