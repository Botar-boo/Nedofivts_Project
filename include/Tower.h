#pragma once
#include "Creep.h"


class Tower : public Unit {
public:
    Tower(userImages& Texture, Vector<float> Pos, unsigned int Price);
    ~Tower() {}
public:
    virtual void Fire(Creep& creep);

    float getReload();
    void setReload(float Time);

    int getPrice();

    void Update(float deltaTime);
    userCircleShape getArea();
    float Timer = 0;

private:
    userCircleShape rangeArea;
    int Price;
    float Reload;
};

class SingleTower : public Tower {
public:
    SingleTower(userImages& Texture, Vector<float> Pos);
    ~SingleTower() {}

    void Fire(Creep& creep);
};

class MultiTower : public Tower {
public:
    MultiTower(userImages& Texture, Vector<float> Pos);

    void Fire(Creep& creep);
private:
    unsigned int shotCount;
};

class FreezingTower : public Tower {
public:
    FreezingTower(userImages& Texture, Vector<float> Pos);
    ~FreezingTower() {}

    void Fire(Creep& creep);
};

class OnePunchTower : public Tower {
public:
    OnePunchTower(userImages& Texture, Vector<float> Pos);
    ~OnePunchTower() {}

    void Fire(Creep& creep);
};