#pragma once
#include "Unit.h"


class Creep : public Unit {
public:
    Creep(tImages& Texture, userSprite& startBlock, vectorU imageCount, float sizeX, float sizeY, float Health, float Speed);
    ~Creep() {}

public:
    void setHealth(float deltaHealth);
    float getHealth();

    void Update(float deltaTime);
    void killCreep(std::vector <Creep>& Creeps, std::vector<std::pair<Creep, float>>& Dead, int creepNumber, float deltaTime);

    void setDirection(int Dir);
    int getDirection();

    void Arrived();
    bool isKilled();

    void setReward(int Reward);
    unsigned int getReward();

    void setSpeed(float Speed);
    float getSpeed();

    void getDamage(Ball Ball);
public:
    std::vector<Ball> ballsFollow;
    float Armor;
    float Evasion;

private:
    unsigned int Reward;
    int Dir;
    bool Killed;
    float Health;
    float Speed;
};

class Batyr : public Creep {
public:
    Batyr(tImages& Texture, unsigned int waveNumber, userSprite& startBlock);
    ~Batyr() {}
};

class Sameer : public Creep {
public:
    Sameer(tImages& Texture, unsigned int waveNumber, userSprite& startBlock);
    ~Sameer() {}
};
