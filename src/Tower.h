#pragma once
#include "Creep.h"


class Tower : public Unit {
public:
    Tower(tImages& Texture, vectorF Pos, unsigned int Price);
    ~Tower() {}
public:
    virtual void Fire(Creep& Creep);

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
    SingleTower(tImages& Texture, vectorF Pos);
    ~SingleTower() {}

    void Fire(Creep& Creep);
};

class MultiTower : public Tower {
public:
    MultiTower(tImages& Texture, vectorF Pos);

    void Fire(Creep& Creep);
private:
    unsigned int shotCount;
};

class FreezingTower : public Tower {
public:
    FreezingTower(tImages& Texture, vectorF Pos);
    ~FreezingTower() {}

    void Fire(Creep& Creep);
};

class OnePunchTower : public Tower {
public:
    OnePunchTower(tImages& Texture, vectorF Pos);
    ~OnePunchTower() {}

    void Fire(Creep& Creep);
};
