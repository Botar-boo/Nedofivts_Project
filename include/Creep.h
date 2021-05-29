#pragma once
#include "Unit.h"

class Creep : public Unit {
public:
    Creep(userImages& Texture, userSprite& startBlock, Vector<int> imageCount, float sizeX, float sizeY, float Health, float Speed);
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

    void startProcessing(float deltaTime, const std::string Event);
    void addBall(Ball& ball);
    std::vector <Ball> getBalls();
    void setMediator(MediatorCreepBall *mediator);

public:
    float Armor;
    float Evasion;
    std::vector<Ball> BallsFlow;

private:
    MediatorCreepBall *Mediator = nullptr;
    unsigned int Reward;
    int Dir;
    bool Killed;
    float Health;
    float Speed;
};

class Batyr : public Creep {
public:
    Batyr(userImages& Texture, unsigned int waveNumber, userSprite& startBlock);
    ~Batyr() {}
};

class Sameer : public Creep {
public:
    Sameer(userImages& Texture, unsigned int waveNumber, userSprite& startBlock);
    ~Sameer() {}
};

class Jegor : public Creep {
public:
    Jegor(userImages& Texture, unsigned int waveNumber, userSprite& startBlock);
    ~Jegor() {}
};

class MediatorCreepBall {
public:
    MediatorCreepBall(){};
    ~MediatorCreepBall() {};

    void processFlight(Creep* creep,float deltaTime);
    void clearBallsFlow(Creep* creep);

};
